#include "Node.h"

#include <cassert>
#include <iostream>
#include <vector>

namespace QApp{
    namespace Kernel {

        template <typename T>
        class PersistentStack {

           using Node = Node<T>;
           using RetType = std::conditional<sizeof(T) < 256, T, T&>;

           template <class U> friend std::ostream &operator << (std::ostream &os, PersistentStack<U> st);


            public:
            PersistentStack() {
              versions_.back().current = 0;
              versions_.back().next = 0;
            }

            size_t currentNumOfVersions() const {
                return versions_.size();
            }

            bool empty(size_t numOfVersion) const {
                assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist");

                return sizesOfVersions_[numOfVersion] == 0;
            }

            void push(T val, size_t numOfVersion) {
                assert(numOfVersion < currentNumOfVersions() && "PUSH: Error! The version you're pushing to does not exist!");

                versions_.reserve(versions_.size() + 1);
                versions_.push_back({std::move(val), currentNumOfVersions(), versions_[numOfVersion].current});
                sizesOfVersions_.push_back(sizesOfVersions_[numOfVersion] + 1);
            }

            void pop(size_t numOfVersion) {
                assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist");
                assert(!empty(numOfVersion) && "POP: Error! Stack is empty!");

                size_t head_index = versions_[numOfVersion].next;
                versions_.push_back(versions_[head_index]);
                sizesOfVersions_.push_back(sizesOfVersions_[numOfVersion] - 1);
            }

            RetType top(size_t numOfVersion) const {
                assert(numOfVersion < currentNumOfVersions() && "TOP: Error! The version you're popping from does not exist!");
                assert(!empty(numOfVersion) && "TOP: Error! Stack is empty!");

                return versions_[numOfVersion].value;
            }

            size_t size(size_t numOfVersion) const {
                assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist!");

                return sizesOfVersions_[numOfVersion];
            }

            void copyVersion(size_t numOfVersion) {
                assert(numOfVersion < currentNumOfVersions() && "Error! This version does not exist");

                versions_.push_back(versions_[numOfVersion]);
                sizesOfVersions_.push_back(sizesOfVersions_[numOfVersion]);
            }

            private:
            std::vector<Node> versions_ = std::vector<Node>(1);
            std::vector<size_t> sizesOfVersions_ = std::vector<size_t>(1, 0);;
        };

        template <typename T>
        std::ostream &operator << (std::ostream &os, PersistentStack<T> st) {
            for (size_t i = 0; i < st.versions_.size(); ++i) {
                os << "Version " << i << ": ";
                Node currentHead = st. versions_[i];
                while (currentHead.next != currentHead.current) {
                    os << currentHead.value << ' ';
                    currentHead = st.versions_[currentHead.next];
                }
                os << '\n';
            }
            return os;
        }
    }// namespace Kernel
}// namespace QApp
