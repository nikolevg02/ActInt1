#include "DataFrame.h"
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Row.h"


/**
 * Parses a log entry string into its constituent components and creates a Row object from them.
 * @param logEntry The log entry string to parse.
 * @return A Row object initialized with the parsed components of the log entry.
 * @complexity O(n) - Where n is the length of the logEntry string. The complexity arises from the operations of parsing the string into components.
 */
Row parseLogEntry(const std::string& logEntry) {
    std::istringstream iss(logEntry);
    std::string month, day, time, ipPort, logMessage;
    iss >> month >> day >> time >> ipPort;
    std::getline(iss, logMessage);


    size_t colonPos = ipPort.find(':');
    std::string ip = ipPort.substr(0, colonPos);
    std::string portStr = ipPort.substr(colonPos + 1);

    return Row(month, day, time, ip, portStr, logMessage);
}

int main() {
    std::vector<Row> rows;
    std::ifstream file("bitacora.txt");
    std::string line;

    while (std::getline(file, line)) {
        rows.push_back(parseLogEntry(line));
    }

    DataFrame df(rows);
    df.radixSort();
    std::string startDate, endDate;
    std::cout << "Enter the start date example (Jun 01 00:22:36): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter the end date example (Jun 02 23:59:59): ";
    std::getline(std::cin, endDate);
    std::istringstream issStart(startDate);
    std::string monthS, dayS, timeS;
    issStart >> monthS >> dayS >> timeS;
    std::istringstream issEnd(endDate);
    std::string monthE, dayE, timeE;
    issEnd >> monthE >> dayE >> timeE;
    Row startTemp = Row(monthS,dayS,timeS,"000.000.000","0000","temp");
    Row endTemp = Row(monthE,dayE,timeE,"000.000.000","0000","temp");
    DataFrame newD =df.trimData(df,startTemp.timeNumber,endTemp.timeNumber);
    newD.saveToFile("bitacora_ordenada.txt");
    newD.Print();

    return 0;
}


// Estructura para representar una fila de datos
struct Row {
    std::string dateTime;
    // Otras propiedades de la fila...

    // Constructor para inicializar la fila con una fecha y hora
    Row(const std::string& dateTime) : dateTime(dateTime) {}
};

// Clase para manejar una Doubly Linked List de filas de datos
class DoublyLinkedList {
private:
    struct Node {
        Row data;
        Node* prev;
        Node* next;
        Node(const Row& data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Método para agregar una fila al final de la lista
    void append(const Row& data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Método para ordenar la lista usando Merge Sort
    void mergeSort() {
        if (!head || !head->next) return; // Caso base: lista vacía o con un solo elemento

        DoublyLinkedList leftHalf, rightHalf;
        split(leftHalf, rightHalf);

        leftHalf.mergeSort();
        rightHalf.mergeSort();

        head = merge(leftHalf.head, rightHalf.head);
    }

    // Método para dividir la lista en dos mitades
    void split(DoublyLinkedList& leftHalf, DoublyLinkedList& rightHalf) {
        Node* slow = head;
        Node* fast = head->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        leftHalf.head = head;
        leftHalf.tail = slow;
        rightHalf.head = slow->next;
        slow->next = nullptr;
        rightHalf.tail = tail;
    }

    // Método para fusionar dos listas ordenadas
    Node* merge(Node* left, Node* right) {
        Node* mergedList = nullptr;
        if (!left) return right;
        if (!right) return left;

        if (left->data.dateTime <= right->data.dateTime) {
            mergedList = left;
            mergedList->next = merge(left->next, right);
            mergedList->next->prev = mergedList;
        } else {
            mergedList = right;
            mergedList->next = merge(left, right->next);
            mergedList->next->prev = mergedList;
        }

        return mergedList;
    }

    // Método para buscar una fecha en la lista usando búsqueda binaria
    bool binarySearch(const std::string& targetDateTime) const {
        Node* current = head;
        while (current) {
            if (current->data.dateTime == targetDateTime) {
                return true;
            } else if (current->data.dateTime < targetDateTime) {
                current = current->next;
            } else {
                return false;
            }
        }
        return false;
    }
};

// Función para solicitar al usuario las fechas de inicio y fin
std::pair<std::string, std::string> getSearchInterval() {
    std::string start, end;
    std::cout << "Ingrese la fecha de inicio en el formato 'MMM DD HH:MM:SS': ";
    std::getline(std::cin, start);
    std::cout << "Ingrese la fecha de fin en el formato 'MMM DD HH:MM:SS': ";
    std::getline(std::cin, end);
    return {start, end};
}

int main() {
    // Crear la lista y leer los datos de un archivo
    DoublyLinkedList list;
    std::ifstream file("data.txt");
    std::string line;
    while (std::getline(file, line)) {
        list.append(Row(line)); // Suponiendo que cada línea del archivo representa una fila de datos
    }

    // Ordenar la lista por fecha y hora
    list.mergeSort();

    // Obtener el intervalo de búsqueda del usuario
    auto [start, end] = getSearchInterval();

    // Buscar las fechas en la lista
    bool startFound = list.binarySearch(start);
    bool endFound = list.binarySearch(end);

    // Verificar si las fechas están presentes en la lista
    if (startFound && endFound) {
        std::cout << "Ambas fechas están presentes en la lista." << std::endl;
    } else {
        std::cout << "Una o ambas fechas no están presentes en la lista." << std::endl;
    }

    return 0;
}
