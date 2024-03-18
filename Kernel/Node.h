#include <cstddef>
namespace Persistent {
    template<typename T>
    struct Node {
        T value;
        size_t current;
        size_t next;
    };
}
