#include "PersistentStack.h"

namespace Persistent {
    template <typename T>
    class PersistentQueue {
        public:
        PersistentQueue() {
            recopy = false;
            copied = false;
            toCopy = 0;

            updateVersion();
        }

        bool empty(int numOfVersion) {
            return versions[numOfVersion].recopy && R.size(versions[numOfVersion].R_Version) == 0;
        }

        void updateVersion() {
            versions.emplace_back(L.currentNumOfVersions()-1, L1.currentNumOfVersions()-1,
                                  R.currentNumOfVersions()-1, R1.currentNumOfVersions()-1, S.currentNumOfVersions()-1,
                                  recopy, copied, toCopy);
        }

        void push(T val, int numOfVersion) {
            assert(numOfVersion < versions.size() && "Error! The version you're pushing to does not exist!");

            if(!versions[numOfVersion].recopy) {
                L.push(val, versions[numOfVersion].L_Version);
                checkRecopy();
            }
            else {
                L1.push(val, versions[numOfVersion].L1_Version);
                checkNormal();
            }
        }

        void pop(int numOfVersion) {
            assert(numOfVersion < versions.size() && "Error! The version you're popping from does not exist!");
            assert(!empty(numOfVersion) && "Error! Queue is empty!");

            if(versions[numOfVersion].recopy) {
                R.pop(versions[numOfVersion].R_Version);
                checkRecopy();
            }
            else {
                R1.pop(versions[numOfVersion].R1_Version);

                if(toCopy > 0) {
                    --toCopy;
                }
                else {
                    R.pop(versions[numOfVersion].R_Version);
                }
                checkNormal();
            }
        }

        void checkRecopy() {
            if(L.size(L.currentNumOfVersions() - 1) > R.size(R.currentNumOfVersions() - 1)) {
                recopy = true;
                toCopy = R.size(R.currentNumOfVersions() - 1);
                copied = false;
                checkNormal();
            }
            else {
                recopy = false;
                updateVersion();
            }
        }

        void checkNormal() {
            additionalOperations();
            recopy = (R.size(R.currentNumOfVersions()-1) != 0);
            updateVersion();
        }

        void additionalOperations() {
            int toDo = 3;
            while(!copied && toDo > 0 && R.size(R.currentNumOfVersions() - 1) > 0) {
                T val = R.top(R.currentNumOfVersions() - 1);
                R.pop(R.currentNumOfVersions() - 1);
                S.push(val, S.currentNumOfVersions() - 1);
                --toDo;
            }

            while(toDo > 0 && L.size(L.currentNumOfVersions() - 1) > 0) {
                copied = true;
                T val = L.top(L.currentNumOfVersions() - 1);
                L.pop(L.currentNumOfVersions() - 1);
                R.push(val, R.currentNumOfVersions() - 1);
                --toDo;
            }

            while(toDo > 0 && S.size(S.currentNumOfVersions() - 1) > 0) {
                T val = S.top(S.currentNumOfVersions() - 1);
                S.pop(S.currentNumOfVersions() - 1);
                if(toCopy > 0) {
                    R.push(val, R.currentNumOfVersions() - 1);
                    --toCopy;
                }
                --toDo;
            }

            if(S.size(S.currentNumOfVersions() - 1) > 0) {
                L.swapStacks(L1);
            }
        }

        private:
        struct queueState {
            int L_Version;
            int L1_Version;
            int R_Version;
            int R1_Version;
            int S_Version;

            bool recopy, copied;
            int toCopy;
            //constructors in structs are stupid, will replace it with sth more reasonable later;

            queueState(int L_, int L1_, int R_, int R1_, int S_, bool recopy_, bool copied_, int toCopy_) :
            L_Version(L_),
            L1_Version(L1_),
            R_Version(R_),
            R1_Version(R1_),
            S_Version(S_),
            recopy(recopy_),
            copied(copied_),
            toCopy(toCopy_) {}
        };

        std::vector<queueState> versions;

        PersistentStack<T> L, L1, R, R1, S;
        bool recopy, copied;
        int toCopy;
    };
}