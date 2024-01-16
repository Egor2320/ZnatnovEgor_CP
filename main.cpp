#include "PersistentQueue.h"

int main() {
//    Persistent::PersistentStack<int> s;
//    s.push(1, 0);
//    s.push(2, 0);
//    s.push(3, 1);
//    s.push(4, 1);
//    s.push(5, 2);
//    s.push(6, s.currentNumOfVersions()-1);
//    s.pop(s.currentNumOfVersions()-1);
//    s.print();

//TODO: -Documentation for the whole project (doxygen)
//      - Unit-tests

    Persistent::PersistentQueue<int> s;
    s.push(1, 0);
    s.push(3, 1);
    s.pop(2);
    s.push(2, 0);
    s.push(4, 2);
    s.pop(1);
    s.pop(5);

    return 0;
}
