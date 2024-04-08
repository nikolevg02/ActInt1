//
// Created by Lou on 4/7/2024.
//

#include "Row.h"
#include <sstream>



Row::Row(std::string month, std::string day, std::string time, std::string ip,std::string port, std::string log) {
    this->month = month;
    this->day = day;
    this->time = time;
    this->ip = ip;
    this->log = log;
    this->port = std::stoi(port);
    this->timeNumber = convertDate(month,day,time);
    this->ipArray = buildIPArray(ip);

}



std::vector<int> Row::buildIPArray(const std::string &ip) {
    std::vector<int> ipArray;
    std::stringstream ss(ip);
    std::string segment;

    while (std::getline(ss, segment, '.')) {
        ipArray.push_back(std::stoi(segment));
    }

    return ipArray;
}

size_t Row::convertDate(const std::string& m, const std::string& d, const std::string & t){
    int totalDays = 0;
    size_t totalSeconds= 0;
    std::vector<int> daysPerMonth = {31,28,31,30,31,30,31,31,30,31,30,31};
    //JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC
    auto addDays = [&daysPerMonth](int nMonth) -> int {
        int counter = 0;
        for (int i = 0; i < nMonth; ++i) {
            counter += daysPerMonth[i];
        }
        return counter;
    };
    auto convertToSeconds = [](const std::string& time) -> int {
        std::istringstream stream(time);
        std::string segment;
        int hours = 0, minutes = 0, seconds = 0, totalSeconds = 0;
        std::getline(stream, segment, ':');
        hours = std::stoi(segment);
        std::getline(stream, segment, ':');
        minutes = std::stoi(segment);
        std::getline(stream, segment);
        seconds = std::stoi(segment);
        // Convert everything to seconds and sum it up
        totalSeconds = hours * 3600 + minutes * 60 + seconds;
        return totalSeconds;
    };


    if(month == "Jan"){ totalDays += addDays(1);}
    else if (month == "Feb"){ totalDays += addDays(2);}
    else if (month == "Mar"){ totalDays += addDays(3);}
    else if (month == "Apr"){ totalDays += addDays(4);}
    else if (month == "May"){ totalDays += addDays(5);}
    else if (month == "Jun"){ totalDays += addDays(6);}
    else if (month == "Jul"){ totalDays += addDays(7);}
    else if (month == "Aug"){ totalDays += addDays(8);}
    else if (month == "Sep"){ totalDays += addDays(9);}
    else if (month == "Oct"){ totalDays += addDays(10);}
    else if (month == "Nov"){ totalDays += addDays(11);}
    else if (month == "Dec"){ totalDays += addDays(12);}
    totalDays = totalDays + stoi(day);
    totalSeconds = convertToSeconds(t) + (totalDays *86400);


    return totalSeconds;
}
