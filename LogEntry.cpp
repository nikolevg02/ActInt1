#include "LogEntry.h"
#include <iostream>

LogEntry::LogEntry(string m, int d, string t, string ip, string r) {
    this->month = m;
    this->day = d;
    this->time = t;
    this->ipAddress = ip;
    this->reason = r;

}

// Method to print the log entry
void LogEntry::print() {
    std::cout << month << " " << day << " " << time << " " << ipAddress << " " << reason << std::endl;
}

// Overload of the < operator to compare entries by date
bool LogEntry::operator<(const LogEntry& other) const {
    string thisDate = month + to_string(day) + time;
    string otherDate = other.month + to_string(other.day) + other.time;
    return thisDate < otherDate;
}

// Function to compare by date
bool LogEntry::compareDate(const string& date) const {
    string thisDate = month + to_string(day) + time;
    return thisDate == date;
}