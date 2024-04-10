
#include "DataFrame.h"
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

/**
 * Default constructor for DataFrame.
 *
 * @complexity O(1)
 */
DataFrame::DataFrame() = default;

/**
 * Constructs a DataFrame instance initialized with provided data.
 *
 * @param inputData Vector of Row containing the initial data.
 * @complexity O(1) - Complexity might vary depending on the operation of std::move.
 */
DataFrame::DataFrame(std::vector<Row> inputData) : Data(std::move(inputData)) {
}

/**
 * Retrieves the digit at the specified position from a number.
 *
 * @param num The number from which to get the digit.
 * @param place The position of the digit to retrieve, starting from 0.
 * @return The digit at the specified position.
 * @complexity O(1)
 */
 int getDigit(int num, int place) {
    return std::abs(num) / static_cast<int>(std::pow(10, place)) % 10;
}

/**
 * Counts the number of digits in an integer.
 *
 * @param num The integer number to count its digits.
 * @return The count of digits in the number.
 * @complexity O(1) - Assuming that the logarithm operation is constant.
 */
 int countDigits(int num) {
    if (num == 0) return 1;
    return std::floor(std::log10(std::abs(num))) + 1;
}
/**
 * Finds the maximum number of digits among all numbers in the provided data.
 *
 * @param data Vector of Row containing the numbers to evaluate.
 * @return The maximum number of digits found.
 * @complexity O(n) - Linear complexity
 */
 int mostDigits(const std::vector<Row>& data) {
    int maxDigits = 0;
    for (const auto& row : data) {
        maxDigits = std::max(maxDigits, countDigits(row.timeNumber));
    }
    return maxDigits;
}
/**
 * Concatenates a vector of vectors into a single vector.
 *
 * @param buckets The vector of vectors to concatenate. Each inner vector is a collection of Row objects.
 * @return A single vector containing all Row objects from the input vectors, concatenated in order.
 * @complexity O(n) - Where n is the total number of Row objects across all vectors. The complexity arises from inserting elements into the result vector.
 */
 std::vector<Row> vectorConcat(const std::vector<std::vector<Row>>& buckets) {
    std::vector<Row> result;
    for (const auto& bucket : buckets) {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }
    return result;
}


/**
 * Sorts the data within the DataFrame using the Radix Sort algorithm.
 * This method specifically sorts based on the 'timeNumber' field of each Row.
 * It distributes the Rows into buckets according to each digit's value (from least to most significant digit),
 * then concatenates these buckets back into the original data array, iteratively improving the sort order.
 *
 * @complexity O(nk) - Where n is the number of Rows in the DataFrame and k is the maximum number of digits
 * in the 'timeNumber' across all Rows. The complexity accounts for distributing Rows into buckets and then
 * concatenating them back, repeated for each digit.
 * @note This method outputs the number of moves and states that there are no comparisons directly to std::cout.
 */
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
/**
 * Sorts the data within the DataFrame using the Bubble Sort algorithm.
 * @complexity O(n^2) - Where n is the number of Rows in the DataFrame. This is because, in the worst case,
 * each element needs to be compared with every other element.
 * @note This method outputs the number of swaps and comparisons directly to std::cout.
 */
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

/**
 * Parses a datetime string into its different parts.
 * @param dateTime The datetime string to parse.
 * @return A vector of strings, where each string is a part of the datetime (year, month, day, hour, minute, second).
 * @complexity O(n) - Where n is the length of the input string. The complexity is derived from iterating over
 * each character in the input string to split it into parts.
 */
std::vector<std::string> parseDateTime(const std::string& dateTime) {
    std::istringstream iss(dateTime);
    std::vector<std::string> parts;
    std::string part;
    while (iss >> part) {
        parts.push_back(part);
    }
    return parts;
}



/**
 * Creates a new DataFrame containing only the rows from the original DataFrame whose 'timeNumber' falls within the specified range.
 * @param origData The original DataFrame to trim data from.
 * @param startDayN The inclusive start of the 'timeNumber' range.
 * @param endDayN The inclusive end of the 'timeNumber' range.
 * @return A new DataFrame containing rows from the original DataFrame that fall within the specified 'timeNumber' range.
 * @complexity O(n) - Where n is the number of rows in the original DataFrame. The complexity comes from needing to iterate through each row once.
 */

DataFrame DataFrame::trimData(DataFrame& origData, int startDayN, int endDayN) {
    DataFrame result;
    for (const auto& row : origData.Data) {
        if (row.timeNumber >= startDayN && row.timeNumber <= endDayN) {
            result.Data.push_back(row);
        }
    }
    return result;
}

/**
 * Saves the DataFrame's data to a file, with each row converted to a string representation followed by a newline.
 * @param filename The name of the file to save the DataFrame's data to.
 * @complexity O(n) - Where n is the number of rows in the DataFrame. The complexity is derived from iterating over each row to write it to the file.
 */
void DataFrame::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : Data) {
        file << row.toString() << std::endl;
    }
    file.close();
}


size_t DataFrame::size() {


    return this->Data.size();
}


/**
 * Prints the contents of the DataFrame to the standard output.
 * @complexity O(n) - Where n is the number of rows in the DataFrame. The complexity arises from the need to iterate through each row and print it.
 */
void DataFrame::Print() {
    for(auto data: this->Data){
        std::cout<<data.month<<" "<<data.day<<" "<<data.time<<" "<<data.ip<<data.port<<" "<<data.log<<std::endl;
    }
}

