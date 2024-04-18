#ifndef ACTINT1_DATAFRAME_H
#define ACTINT1_DATAFRAME_H

#include <vector>
#include "Row.h"

class DataFrame {
public:
    std::vector<Row> Data;

    // Default constructor initializes with an empty DataFrame
    DataFrame();

    // Constructor for initializing with a vector of Rows
    DataFrame(std::vector<Row> inputData);
    void radixSort();
    void bubbleSort();

    // Function declaration for binary search
    int binarySearch(const std::vector<Row>& data, size_t targetTimeNumber);

    int binarySearch(const std::string &dateTime, bool searchFirst);
    int compareTo(const std::string& dateTime) const;

    void displayRecordsInRange(const std::string& start, const std::string& end);
    void saveToFile(const std::string& filename);
    DataFrame segmentData(std::string start, std::string end);

    int binarySearchByTimeNumber(size_t referenceTimeNumber);
    DataFrame trimData(DataFrame&  origData, int startDayN, int endDayN);
    size_t size();
    void Print();
};

#endif //ACTINT1_DATAFRAME_H

