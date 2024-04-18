#include "DataFrame.h"
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

// Default constructor for DataFrame
DataFrame::DataFrame() = default;

// Constructs a DataFrame instance initialized with provided data
DataFrame::DataFrame(std::vector<Row> inputData) : Data(std::move(inputData)) {
}

// Retrieves the digit at the specified position from a number
int getDigit(int num, int place) {
    return std::abs(num) / static_cast<int>(std::pow(10, place)) % 10;
}

// Counts the number of digits in an integer
int countDigits(int num) {
    if (num == 0) return 1;
    return std::floor(std::log10(std::abs(num))) + 1;
}

// Finds the maximum number of digits among all numbers in the provided data
int mostDigits(const std::vector<Row>& data) {
    int maxDigits = 0;
    for (const auto& row : data) {
        maxDigits = std::max(maxDigits, countDigits(row.timeNumber));
    }
    return maxDigits;
}

// Concatenates a vector of vectors into a single vector
std::vector<Row> vectorConcat(const std::vector<std::vector<Row>>& buckets) {
    std::vector<Row> result;
    for (const auto& bucket : buckets) {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }
    return result;
}

// Sorts the data within the DataFrame using the Radix Sort algorithm
void DataFrame::radixSort() {
    if (Data.empty()) return;
    int moveCount = 0;
    int maxDigitCount = mostDigits(Data);
    for (int k = 0; k < maxDigitCount; ++k) {
        std::vector<std::vector<Row>> buckets(10);
        for (auto &row: Data) {
            int digit = getDigit(row.timeNumber, k);
            buckets[digit].push_back(row);
            moveCount++;
        }
        Data = vectorConcat(buckets);
    }
    std::cout << "Radix Sort - Moves: " << moveCount << ", Comparisons: None" << std::endl;
}

// Sorts the data within the DataFrame using the Bubble Sort algorithm
void DataFrame::bubbleSort() {
    bool swapped;
    int swapCount = 0;
    int comparisonCount = 0;
    do {
        swapped = false;
        for (size_t i = 1; i < Data.size(); ++i) {
            comparisonCount++;
            if (Data[i - 1] > Data[i]) {
                std::swap(Data[i - 1], Data[i]);
                swapped = true;
                swapCount++;
            }
        }
    } while (swapped);
    std::cout << "Bubble Sort - Swaps: " << swapCount << ", Comparisons: " << comparisonCount << std::endl;
}

// Parses a datetime string into its different parts
std::vector<std::string> parseDateTime(const std::string& dateTime) {
    std::istringstream iss(dateTime);
    std::vector<std::string> parts;
    std::string part;
    while (iss >> part) {
        parts.push_back(part);
    }
    return parts;
}

// Creates a new DataFrame containing only the rows from the original DataFrame whose 'timeNumber' falls within the specified range
DataFrame DataFrame::trimData(DataFrame& origData, int startDayN, int endDayN) {
    DataFrame result;
    for (const auto& row : origData.Data) {
        if (row.timeNumber >= startDayN && row.timeNumber <= endDayN) {
            result.Data.push_back(row);
        }
    }
    return result;
}

// Saves the DataFrame's data to a file, with each row converted to a string representation followed by a newline
void DataFrame::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : Data) {
        file << row.toString() << std::endl;
    }
    file.close();
}

// Returns the size of the DataFrame
size_t DataFrame::size() {
    return this->Data.size();
}

// Prints the contents of the DataFrame to the standard output
void DataFrame::Print() {
    for(auto data: this->Data){
        std::cout<<data.month<<" "<<data.day<<" "<<data.time<<" "<<data.ip<<data.port<<" "<<data.log<<std::endl;
    }
}
