#include "DataFrame.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Row.h"
#include "DLinkedList.h"


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
    DLinkedList<Row> myList;
    std::ifstream file("bitacora.txt");
    std::string line;

    while (std::getline(file, line)) {
        myList.addFirst(parseLogEntry(line));

    }

    DLinkedList<Row> df;
    df.sort();
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

   /* // Create a doubly linked list for Row objects
    DLinkedList<Row> myList;

    // Create Row objects with different times
    Row row1("Jan", "1", "12:00:00", "192.168.1.1", "8080", "User logged in");
    Row row2("Jan", "1", "12:05:00", "192.168.1.2", "8080", "User logged out");
    Row row3("Jan", "1", "11:55:00", "192.168.1.3", "8080", "Server started");
    Row row4("Jan", "1", "12:10:00", "192.168.1.4", "8080", "Server shutdown");

    // Add rows to the list
    myList.addLast(row1);
    myList.addLast(row2);
    myList.addLast(row3);
    myList.addLast(row4);

    // Display the list before sorting
    std::cout << "List before sorting:" << std::endl;
    myList.printList();

    // Sort the list
    myList.sortMerge();
    // Display the list after sorting
    std::cout << "List after sorting:" << std::endl;
    myList.printList();*/
}