#include <cstddef>
namespace QApp{
    namespace Kernel {
        template<typename T>
        struct Node {
            T value;
            size_t current;
            size_t next;
        };
    }// namespace Kernel
}// namespace QApp
