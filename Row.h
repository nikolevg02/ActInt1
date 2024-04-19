//
// Created by Lou on 4/7/2024.
//

#include <iostream>
#include <vector>
#ifndef ACTINT1_ROW_H
#define ACTINT1_ROW_H


class Row {
public:
    std::string month;
    std::string day;
    std::string time;
    std::string ip;
    int port;
    std::string log;
    size_t timeNumber;
    std::vector<int> ipArray;



    Row(std::string m, std::string d, std::string t, std::string i,std::string p, std::string l);

    static std::vector<int> buildIPArray(const std::string& ip);

    size_t convertDate(const std::string& month, const std::string& day, const std::string& time);

    bool operator<(const Row& other) const {
        return this->timeNumber < other.timeNumber;
    }

    // Operator> for comparison
    bool operator>(const Row& other) const {
        return this->timeNumber > other.timeNumber;
    }

    friend std::ostream& operator<<(std::ostream& os, const Row& row) {
        os << row.month << " " << row.day << " " << row.time << " " << row.ip << " " << row.port << " " << row.log;
        return os;
    }
    std::string toString() const; // Declaration


};


#endif //ACTINT1_ROW_H
