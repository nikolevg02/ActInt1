
#include "DataFrame.h"
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>


DataFrame::DataFrame() = default;
DataFrame::DataFrame(std::vector<Row> inputData) : Data(std::move(inputData)) {
}
 int getDigit(int num, int place) {
    return std::abs(num) / static_cast<int>(std::pow(10, place)) % 10;
}


 int countDigits(int num) {
    if (num == 0) return 1;
    return std::floor(std::log10(std::abs(num))) + 1;
}

 int mostDigits(const std::vector<Row>& data) {
    int maxDigits = 0;
    for (const auto& row : data) {
        maxDigits = std::max(maxDigits, countDigits(row.timeNumber));
    }
    return maxDigits;
}

 std::vector<Row> vectorConcat(const std::vector<std::vector<Row>>& buckets) {
    std::vector<Row> result;
    for (const auto& bucket : buckets) {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }
    return result;
}



void DataFrame::radixSort() {
    // Implementation directly manipulates `Data`, no need to pass it
    if (Data.empty()) return;
    int moveCount = 0;
    // Logic remains the same, but it operates on `this->Data`
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
void DataFrame::bubbleSort() {
    bool swapped;
    int swapCount = 0;
    int comparisonCount = 0;

    do {
        swapped = false;
        for (size_t i = 1; i < Data.size(); ++i) {
            comparisonCount++; // Increment comparison count here
            if (Data[i - 1] > Data[i]) {
                std::swap(Data[i - 1], Data[i]);
                swapped = true;
                swapCount++; // Increment swap count here
            }
        }
    } while (swapped);

    // Print the counts
    std::cout << "Bubble Sort - Swaps: " << swapCount << ", Comparisons: " << comparisonCount << std::endl;
}

// Helper function to parse the dateTime string
std::vector<std::string> parseDateTime(const std::string& dateTime) {
    std::istringstream iss(dateTime);
    std::vector<std::string> parts;
    std::string part;
    while (iss >> part) {
        parts.push_back(part);
    }
    return parts;
}

int Row::compareTo(const std::string& dateTime) const {
    auto dateTimeParts = parseDateTime(dateTime);

    // Assuming the format is always correct and parts.size() == 4 (month, day, time)
    std::string inputMonth = dateTimeParts[0];
    std::string inputDay = dateTimeParts[1];
    std::string inputTime = dateTimeParts[2] + " " + dateTimeParts[3]; // Concatenate to match format

    // Compare month, day, and time
    if (month < inputMonth) return -1;
    else if (month > inputMonth) return 1;
    else { // Months are equal, compare days
        if (day < inputDay) return -1;
        else if (day > inputDay) return 1;
        else { // Days are equal, compare time
            if (time < inputTime) return -1;
            else if (time > inputTime) return 1;
            else return 0; // Equal
        }
    }
}


int DataFrame::binarySearch(const std::string& dateTime, bool searchFirst) {
    int low = 0;
    int high = Data.size() - 1;
    int result = -1; // -1 indicates not found

    while (low <= high) {
        int mid = low + (high - low) / 2;
        // Assuming Row objects can be directly compared with dateTime strings
        // You may need to adjust this comparison to match your data structure
        if (Data[mid].compareTo(dateTime) == 0) {
            result = mid; // Found a match
            // If searching for first occurrence, move left
            if (searchFirst) {
                high = mid - 1;
            }
                // If searching for last occurrence, move right
            else {
                low = mid + 1;
            }
        }
        else if (Data[mid].compareTo(dateTime) < 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}


void DataFrame::displayRecordsInRange(const std::string& start, const std::string& end) {
    // Convert start and end to comparable format
    auto startComparable = Row::convertToDate(start);
    auto endComparable = Row::convertToDate(end);

    // Implement binary search to find the start and end indices
    int startIndex = binarySearch(startComparable, true); // True for finding the start date
    int endIndex = binarySearch(endComparable, false); // False for finding the end date

    // Verify both dates are found
    if (startIndex == -1 || endIndex == -1) {
        std::cout << "One or both dates not found in the log." << std::endl;
        return;
    }

    // Display records
    for (int i = startIndex; i <= endIndex; ++i) {
        std::cout << Data[i].toString() << std::endl; // Assuming toString method exists
    }
}

void DataFrame::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : Data) {
        file << row.toString() << std::endl; // Assuming toString method exists
    }
    file.close();
}