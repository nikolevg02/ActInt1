#include "DataFrame.h"
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