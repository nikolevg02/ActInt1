/*

#include "Row.h"
#include <iostream>
#include <string>
#include <sstream>
int main(){




        // The time string
     */
/*   std::string time = "18:43:58";

        // Lambda to process the time string
        auto convertToSeconds = [](const std::string& time) -> int {
            std::istringstream stream(time);
            std::string segment;
            int hours = 0, minutes = 0, seconds = 0, totalSeconds = 0;

            // Get hours
            std::getline(stream, segment, ':');
            hours = std::stoi(segment);

            // Get minutes
            std::getline(stream, segment, ':');
            minutes = std::stoi(segment);

            // Get seconds
            std::getline(stream, segment);
            seconds = std::stoi(segment);

            // Convert everything to seconds and sum it up
            totalSeconds = hours * 3600 + minutes * 60 + seconds;
            std::cout<< hours<<std::endl;
            std::cout<< minutes<<std::endl;
            std::cout<< seconds<<std::endl;

            return totalSeconds;
        };

        // Use the lambda and print the result
        int totalSeconds = convertToSeconds(time);
        std::cout << "Total seconds: " << totalSeconds << std::endl;
*//*



        Row Row(Sep 23 12:58:18 80.169.79.65:1150 "Failed password for illegal user root")
        return 0;
    }
*/
#include "DataFrame.h"
#include <fstream>
#include <iostream>
#include <sstream>


// Utility function to parse a log line and create a Row object.
Row parseLogEntry(const std::string& logEntry) {
    std::istringstream iss(logEntry);
    std::string month, day, time, ipPort, logMessage;
    iss >> month >> day >> time >> ipPort;
    std::getline(iss, logMessage); // Capture the rest of the entry as the log message.

    // Extract IP and port.
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
    std::cout << "Enter the start date (Jun 01 00:22:36): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter the end date (Jun 02 23:59:59): ";
    std::getline(std::cin, endDate);

    df.displayRecordsInRange(startDate, endDate);
    df.saveToFile("bitacora_ordenada.txt");

    // Print the sorted data.
   /* for (const auto& row : df.Data) {
        std::cout << row.month << " " << row.day << " " << row.time << " " << row.ip << ":" << row.port << " " << row.log << std::endl;
    }*/

    return 0;
}