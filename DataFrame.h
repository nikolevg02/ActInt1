

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

};


#endif //ACTINT1_DATAFRAME_H
