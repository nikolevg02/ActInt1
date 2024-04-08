

#ifndef ACTINT1_DATAFRAME_H
#define ACTINT1_DATAFRAME_H

#include <vector>
#include "Row.h"
class DataFrame {
public:
    std::vector<Row>Data;

    // Default constructor initializes with an empty DataFrame
    DataFrame();

    // Constructor for initializing with a vector of Rows
    DataFrame(std::vector<Row> inputData);
    void radixSort();
    void bubbleSort();


    int binarySearch(const std::string &dateTime, bool searchFirst);
    int compareTo(const std::string& dateTime) const;

    void displayRecordsInRange(const std::string& start, const std::string& end);
    void saveToFile(const std::string& filename);
};


#endif //ACTINT1_DATAFRAME_H
