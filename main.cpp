#include "Except.h"
#include "Kernel/PersistentStack.h"
#include "QRuntime.h"

#include <vector>

int main(int argc, char** argv) {
    //QApp::QRuntime runtime(argc, argv);
    try{
        QApp::Kernel::PersistentStack<int> s;
        std::vector<QApp::Kernel::ActionRequest<int>> req;
        req.push_back({'P', 1, 0});
        req.push_back({'P', 2, 0});
        req.push_back({'P', 3, 1});
        req.push_back({'P', 4, 1});
        req.push_back({'P', 5, 2});
        req.push_back({'P', 6, s.currentNumOfVersions()-1});
        req.push_back({'D', -1, s.currentNumOfVersions()});
        req.push_back({'P', 8, 4});
        req.push_back({'D', -1, 4});
        req.push_back({'D', -1, 8});


        for (auto& request : req) {
            s.perform_action(request);
        }
        std::cout << s;

    } catch (...) {
        QApp::Except::react();
    }
    return 0;
}
