//
// Created by Lou on 4/17/2024.
//

#include "DLLNode.h"

template <class T>
DLLNode<T>::DLLNode() : data{}, next{nullptr}, prev{nullptr}{}

template <class T>
DLLNode<T>::DLLNode(T value) : data{value}, next{nullptr}, prev{nullptr} {}