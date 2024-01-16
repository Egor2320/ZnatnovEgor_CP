#include "Node.h"

namespace Persistent {

    template <typename T>
    class PersistentStack {
        public:
        PersistentStack() {
            versions.resize(1, nullptr);
            sizesOfVersions.resize(1, 0);
            currentSize = 0;
        }

        ~PersistentStack() {
            for (auto node : unique_nodes) {
                delete node;
            }
        }

        std::size_t currentNumOfVersions() {
            return versions.size();
        }

        bool empty(int numOfVersion) {
            assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist");

            return sizesOfVersions[numOfVersion] == 0;
        }

        void push(T value, int numOfVersion) {
            assert(numOfVersion < currentNumOfVersions() && "PUSH: Error! The version you're pushing to does not exist!");

            versions.push_back(new Node(value, versions[numOfVersion]));
            unique_nodes.push_back(versions.back());
            currentSize = sizesOfVersions[numOfVersion] + 1;
            sizesOfVersions.push_back(currentSize);
        }

        void pop(int numOfVersion) {
            assert(!empty(numOfVersion) && "POP: Error! Stack is empty!");

            versions.push_back(versions[numOfVersion]->next);
            currentSize = sizesOfVersions[numOfVersion] - 1;
            sizesOfVersions.push_back(currentSize);
        }

        T top(int numOfVersion) {
            assert(numOfVersion < currentNumOfVersions() && "TOP: Error! The version you're popping from does not exist!");
            assert(!empty(numOfVersion) && "TOP: Error! Stack is empty!");

            return versions[numOfVersion]->value;
        }

        std::size_t size(int numOfVersion) {
            assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist!");

            return sizesOfVersions[numOfVersion];
        }

        void print() {
            for (int i = 0; i < versions.size(); ++i) {
                std::cout << "Version " << i << ": ";
                Persistent::Node<T> *currentHead = versions[i];
                while (currentHead) {
                    std::cout << currentHead->value << ' ';
                    currentHead = currentHead->next;
                }
                std::cout << '\n';
            }
        }

        void swapStacks(PersistentStack<T> &other) {
            std::swap(this->versions, other.versions);
            std::swap(this->sizesOfVersions, other.sizesOfVersions);
            std::swap(this->currentSize, other.currentSize);
        }

        void copyVersion(int numOfVersion) {
            assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist");

            versions.push_back(versions[numOfVersion]);
            sizesOfVersions.push_back(sizesOfVersions[numOfVersion]);
        }

        private:
        std::vector<Persistent::Node<T> *> versions;
        std::vector<size_t> sizesOfVersions;
        std::vector<Persistent::Node<T> *> unique_nodes;
        size_t currentSize;

    };
}