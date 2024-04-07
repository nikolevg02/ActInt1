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
    std::string log;
    int timeNumber;
    std::vector<int> ipArray;
    int logNumber;

    Row(std::string m, std::string d, std::string t, std::string i, std::string l,  int tn, std::vector<int> ipA, int ln);

    static std::vector<int> buildIPArray(const std::string& ip);

    size_t convertDate(const std::string& month, const std::string& day, const std::string& time);

};


#endif //ACTINT1_ROW_H
