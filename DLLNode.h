//
// Created by Lou on 4/17/2024.
//

#ifndef ACTINT1_DLLNODE_H
#define ACTINT1_DLLNODE_H

template <class T>
class DLLNode {
private:
    DLLNode<T> *prev;

public:
    DLLNode();
    DLLNode(T value);

    // El template LinkedList<U> tiene acceso a los elementos privados de esta clase
    template<typename U> friend class DLinkedList;

    DLLNode<T> *next;
    T data;
};

#include "DLLNode.tpp"

#endif //ACTINT1_DLLNODE_H
