//
// Created by Lou on 4/17/2024.
//

#ifndef ACTINT1_DLINKEDLIST_H
#define ACTINT1_DLINKEDLIST_H
#include <iostream>
#include <stdexcept>
#include "DLLNode.h"
template <class T>
class DLinkedList {
private:
    //DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;

public:

    DLLNode<T> *head;
    DLinkedList();
    ~DLinkedList();
    int getNumElements();
    void printList();
    void printReverseList();
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);
    void updateData(T value, T newValue);
    void updateAt(int position, T newValue);
    int findData(T value);
    void invert();
    void sort();
    int getProductSublist(int ini, int fin);
    void sortMerge();

    DLinkedList<Row> trimData(size_t startDayN, size_t endDayN);
private:
    void quickSort(DLLNode<T> *low, DLLNode<T> *high);
    DLLNode<T>* partition(DLLNode<T> *low, DLLNode<T> *high);
};



#include "DLinkedList.tpp"
#endif //ACTINT1_DLINKEDLIST_H
