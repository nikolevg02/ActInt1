
#include "Row.h"
#include <sstream>
#include <unordered_map>

/**
 * Constructor for the Row class that initializes a row with the provided data.
 * @param month The month component of the row's date.
 * @param day The day component of the row's date.
 * @param time The time of day for the row's timestamp.
 * @param ip The IP address associated with the row.
 * @param port The port number associated with the row, as a string to be converted to integer.
 * @param log The log message associated with the row.
 * @complexity O(1) - Assuming 'convertDate' and 'buildIPArray' functions operate in constant time. The actual complexity might vary based on the implementations of these functions.
 */
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
/**
 * Converts the Row's data to a string representation.
 * @return A string representation of the Row's data.
 * @complexity O(1) - The complexity is constant, assuming string concatenation and integer-to-string conversion are constant time operations.
 */
std::string Row::toString() const {
    return month + " " + day + " " + time + " " + ip + " " + std::to_string(port) + " " + log;
}

/**
 * Builds an array of integers from an IP address string.
 *
 * Takes an IP address in string format, splits it into its constituent segments based on the '.' delimiter,
 * and converts each segment into an integer. These integers are then stored in a vector, effectively transforming
 * the dotted decimal notation of an IP address into a numeric array representation.
 *
 * @param ip The IP address string to be converted into an array of integers.
 * @return A vector of integers, each representing a segment of the IP address.
 * @complexity O(n) - Where n is the number of characters in the IP address string. The complexity arises from
 * iterating through the string to split it into segments and converting those segments to integers.
 */
std::vector<int> Row::buildIPArray(const std::string &ip) {
    std::vector<int> ipArray;
    std::stringstream ss(ip);
    std::string segment;

    while (std::getline(ss, segment, '.')) {
        ipArray.push_back(std::stoi(segment));
    }

    return ipArray;
}
/**
 * Converts a date and time into a total number of seconds.
 * @param m The month part of the date as a three-letter abbreviation (e.g., "Jan", "Feb").
 * @param d The day part of the date.
 * @param t The time in "HH:MM:SS" format.
 * @return The total number of seconds represented by the input date and time since the beginning of the year.
 * @complexity O(1) - While there are loops and iterations, their operations are bounded by a constant (the size of the daysPerMonth vector and the fixed format of the time), leading to constant complexity.
 */
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





