#include "Except.h"
#include "Kernel/PersistentStack.h"

int main() {
    try{
        QApp::Persistent::PersistentStack<int> s;
        s.push(1, 0);
        s.push(2, 0);
        s.push(3, 1);
        s.push(4, 1);
        s.push(5, 2);
        s.push(6, s.currentNumOfVersions()-1);
        s.pop(s.currentNumOfVersions()-1);
        s.push(8, 4);
        s.pop(4);
        std::cout << s;
    } catch (...) {
        QApp::Except::react();
    }
    return 0;
}
