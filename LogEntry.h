//
// Created by Lou on 4/5/2024.
//

#ifndef ACTINT1_LOGENTRY_H
#define ACTINT1_LOGENTRY_H
#include <string>

using namespace std;
class LogEntry {
public:
    string month;
    int day;
    string time;
    string ipAddress;
    string reason;

    // Constructor
    LogEntry(string m, int d, string t, string ip, string r);

    // Method to print the log entry
    void print();

    // Overload of the < operator to compare entries by date
    bool operator<(const LogEntry& other) const;

    // Function to compare by date
    bool compareDate(const string& date) const;
};


#endif //ACTINT1_LOGENTRY_H
