#include <cstdint>

namespace QApp {
    namespace Kernel {
        template<typename T>
        struct ActionRequest {
            char actionCode;
            T value;
            size_t version;
        };
    }// namespace Kernel
}// namespace QApp
