#include <cstddef>
namespace QApp{
    namespace Persistent {
        template<typename T>
        struct Node {
            T value;
            size_t current;
            size_t next;
        };
    }
}
