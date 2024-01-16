#include <cassert>
#include <iostream>
#include <vector>

namespace Persistent {
    template<typename T>
    class Node {
        public:
        T value;
        Node<T> *next;
        Node(T _value, Node<T> *_next) : value(_value), next(_next) {}
    };
}