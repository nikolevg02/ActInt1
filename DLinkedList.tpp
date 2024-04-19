//
// Created by Lou on 4/17/2024.
//

#include "DLinkedList.h"
#include <utility> // For std::swap
#include "DLLNode.h"
#include "Row.h"

// Complejidad O(1)
template <class T>
DLinkedList<T>::DLinkedList() {
    std::cout << "--> Creando una lista doblemente ligada vacia: " << this << std::endl;
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}



// Complejidad O(n)
template <class T>
DLinkedList<T>::~DLinkedList() {
    std::cout << "--> Liberando memoria de la lista doblemente ligada: " << this << std::endl;
    DLLNode<T> *p, *q;
    p = head;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

// Complejidad O(1)
template <class T>
int DLinkedList<T>::getNumElements() {
    return numElements;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::printList() {
    if (head == nullptr && tail == nullptr)
        std::cout << "La lista esta vacia" << std::endl;
    else {
        std::cout << "El contenido de la lista es: " << std::endl;
        DLLNode<T> *p = head;
        while(p != nullptr) {
            std::cout << p->data << "\n";
            p = p->next;
        }
        std::cout << std::endl;
    }
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::printReverseList() {
    if (head == nullptr && tail == nullptr)
        std::cout << "La lista esta vacia" << std::endl;
    else {
        std::cout << "El contenido inverso de la lista es: " << std::endl;
        DLLNode<T> *p = tail;
        while(p != nullptr) {
            std::cout << p->data << " ";
            p = p->prev;
        }
        std::cout << std::endl;
    }
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addFirst(T value) {
    // 1. crear nuevo nodo
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // si la lista esta vacia
    if (head == nullptr && tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        // 2. apuntar newNode->next al nodo apuntado por head
        newNode->next = head;
        // 3. apuntar head->prev a newNode
        head->prev = newNode;
        // 4. actualizar head para apuntar a newNode
        head = newNode;
    }
    numElements++;
}

// Complejidad O(1)
template <class T>
void DLinkedList<T>::addLast(T value) {
    // La lista esta vacia
    if (head == nullptr && tail == nullptr)
        addFirst(value);
    else {
        // 1. crear nuevo nodo
        DLLNode<T> *newNode = new DLLNode<T>(value);
        // 2. apuntar tail->next a newNode
        tail->next = newNode;
        // 3. apuntar newNode->prev a tail
        newNode->prev = tail;
        // 4. actualizar tail para apuntar a newNode
        tail = newNode;
        numElements++;
    }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteData(T value) {
    // La lista esta vacia
    if (head == nullptr && tail == nullptr) {
        std::cout << "La lista esta vacia" << std::endl;
        return false;
    }
    else {
        // Buscar value en la lista
        DLLNode<T> *p = head;
        DLLNode<T> *previous = nullptr;
        while(p != nullptr && p->data != value) {
            previous = p;
            p = p->next;
        }
        // si value no esta en la lista
        if (p == nullptr) {
            std::cout << "El valor no existe en la lista" << std::endl;
            return false;
        }
        // si debo borrar el primer nodo de la lista
        if (p != nullptr && p == head) {
            head = p->next;
            if (head == nullptr) // habia solo un nodo en la lista
                tail = nullptr;
            else
                head->prev = nullptr;
        }
        else if (p->next == nullptr) { // borrar el ultimo nodo
            previous->next = nullptr;
            tail = previous;
        }
        else { // borrar cualquier otro nodo
            previous->next = p->next;
            p->next->prev = previous;
        }
        // borrar el nodo apuntado por p
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
}

// Complejidad O(n)
template <class T>
bool DLinkedList<T>::deleteAt(int position) {
    // La lista esta vacia
    if (position < 0 || position >= numElements) {
        throw std::out_of_range("Indice fuera de rango");
    }
    else if (position == 0) { // primer nodo
        DLLNode<T> *p = head;
        // si la lista contiene un solo nodo
        if (p != nullptr && p->next == nullptr) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = p->next;
            head->prev = nullptr;
        }
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
    else {
        // Buscar position en la lista
        DLLNode<T> *p = head;
        DLLNode<T> *previous = nullptr;
        int index = 0;
        while(index != position) {
            previous = p;
            p = p->next;
            index++;
        }
        // debo borrar el ultimo nodo
        if (p->next == nullptr) {
            previous->next = nullptr;
            tail = previous;
        }
        else { // borrar cualquier otro nodo
            previous->next = p->next;
            p->next->prev = previous;
        }
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
}

// Complejidad O(n)
template <class T>
T DLinkedList<T>::getData(int position) {
    // Validar position
    if (position < 0 || position >= numElements) {
        throw std::out_of_range("Indice fuera de rango");
    }
    else if (position == 0) { // primer nodo
        return head->data;
    }
    else { // si es cualquier otra posicion
        // Buscar position en la lista
        DLLNode<T> *p = head;
        int index = 0;
        while(index != position) {
            p = p->next;
            index++;
        }
        if (p != nullptr)
            return p->data;
        else
            return {};
    }
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::updateData(T value, T newValue) {
    // Buscar value en la lista
    DLLNode<T> *p = head;
    while(p != nullptr && p->data != value) {
        p = p->next;
    }
    if (p != nullptr)
        p->data = newValue;
    else
        throw std::out_of_range("El elemento a actualizar no existe en la lista");
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::updateAt(int position, T newValue) {
    // Validar que la posición sea válida
    if (position < 0 || position >= numElements) {
        throw std::out_of_range("Indice fuera de rango");
    }
    // Encontrar el nodo en la posición dada
    DLLNode<T> *current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    // Actualizar el valor del nodo
    if (current != nullptr) {
        current->data = newValue;
    }
}

// Complejidad O(n)
template <class T>
int DLinkedList<T>::findData(T value) {
    DLLNode<T> *current = head;
    int position = 0;
    while (current != nullptr) {
        if (current->data == value) {
            // Devuelve la posición actual si encuentra el valor
            return position;
        }
        current = current->next;
        position++;
    }
    // Devuelve -1 si no encuentra el valor
    return -1;
}

// Complejidad O(n)
template <class T>
void DLinkedList<T>::invert() {
    DLLNode<T> *current = head;
    DLLNode<T> *temp = nullptr;
    // Intercambiar head y tail al finalizar
    tail = head;
    // Iterar sobre la lista y cambiar los punteros next y prev de cada nodo
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    // Ajustar head al nuevo primer nodo, que es el último nodo antes de invertir
    if(temp != nullptr) {
        head = temp->prev;
    }
}

// Complejidad O(n log n)
template <class T>
void DLinkedList<T>::sort() {
    // Llamar a la función de ayuda para ordenar la lista usando el algoritmo quicksort
    quickSort(head, tail);
}

// Función de ayuda para el algoritmo quicksort
template <class T>
void DLinkedList<T>::quickSort(DLLNode<T> *low, DLLNode<T> *high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
        DLLNode<T> *pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}

// Función de partición para el algoritmo quicksort
template <class T>
DLLNode<T>* DLinkedList<T>::partition(DLLNode<T> *low, DLLNode<T> *high) {
    T pivotValue = high->data;
    DLLNode<T> *i = low->prev;
    for (DLLNode<T> *j = low; j != high; j = j->next) {
        if (j->data < pivotValue) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}

// Complejidad O(n)
template <class T>
int DLinkedList<T>::getProductSublist(int ini, int fin) {
    if (ini < 0 || fin >= numElements || ini > fin) {
        throw std::out_of_range("Índices de sublist fuera de rango");
    }
    // Encontrar el nodo en la posición inicial
    DLLNode<T> *current = head;
    for (int i = 0; i < ini; ++i) {
        current = current->next;
    }
    // Inicializar el producto como el valor del nodo en la posición inicial
    int product = current->data;
    // Recorrer la lista desde la posición inicial hasta la posición final
    for (int i = ini + 1; i <= fin; ++i) {
        current = current->next;
        // Multiplicar el producto actual por el valor del nodo actual
        product *= current->data;
    }
    return product;
}

/*template<class T>
DLLNode<T>* mergeSort(DLLNode<T>* &head) {
    if (!head || !head->next) {
        return;
    }

    DLLNode<T>* second = split(head);

    mergeSort(head);
    mergeSort(second);

    head = merge(head, second);
}
template<class T>
DLLNode<T>* split(DLLNode<T>* head) {
    DLLNode<T>* fast = head;
    DLLNode<T>* slow = head;
    DLLNode<T>* prev = nullptr;

    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev) {
        prev->next = nullptr;
    }

    return slow;
}

template<class T>
DLLNode<T>* merge(DLLNode<T>* first, DLLNode<T>* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

template<class T>
void DLinkedList<T>::sortMerge() {
    if (head != nullptr) {
        head = mergeSort(head);  // This should start the merge sort process correctly
    }*/
/*
}*/

template<class T>
DLLNode<T>* mergeSort(DLLNode<T>* head) {
    if (!head || !head->next) {
        return head;
    }

    // Split the list into halves
    DLLNode<T>* second = split(head);

    // Recursively sort both halves
    DLLNode<T>* left = mergeSort(head);
    DLLNode<T>* right = mergeSort(second);

    // Merge sorted halves
    return merge(left, right);
}

template<class T>
DLLNode<T>* split(DLLNode<T>* head) {
    DLLNode<T>* fast = head, *slow = head;
    DLLNode<T>* prev = nullptr;

    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev) {
        prev->next = nullptr; // Split the list into two halves
    }

    return slow; // Return the start of the second half
}

template<class T>
DLLNode<T>* merge(DLLNode<T>* first, DLLNode<T>* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        if (first->next) first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        if (second->next) second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

// Wrapper function to initiate merge sort
template<class T>
void DLinkedList<T>::sortMerge() {
    head = mergeSort(head);  // Start merge sort
    // Adjust tail pointer
    DLLNode<T>* temp = head;
    while (temp && temp->next) {
        temp = temp->next;
    }
    tail = temp; // Update the tail pointer after sorting
}


DLinkedList<Row> trimData(DLinkedList<Row>& origData, int startDayN, int endDayN) {
    DLinkedList<Row> result;
    DLLNode<Row>* current = origData.head; // Assuming there's a getHead() method to access the head node.

    while (current != nullptr) {
        if (current->data.timeNumber >= startDayN && current->data.timeNumber <= endDayN) {
            result.addLast(current->data); // Using addLast to append to the result list.
        }
        current = current->next; // Move to the next node.
    }

    return result;
}