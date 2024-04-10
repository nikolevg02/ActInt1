
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


/*
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
*/

/* DataFrame DataFrame::trimData(DataFrame &origData, int startDayN, int endDayN) {
    int startIndex = -1;
    int endIndex = -1;

    // Find start and end indices in a single pass
    for (int i = 0; i < origData.size(); ++i) {
        if (startIndex == -1 && origData.Data[i].timeNumber >= startDayN) {
            startIndex = i; // Set start index when we find the first matching or exceeding dayNumber
        }
        if (origData.Data[i].timeNumber <= endDayN) {
            endIndex = i; // Update end index while we are within or equal to the endDayN
        }
    }

    // Check if valid segment was found
    if (startIndex == -1 || endIndex == -1 || startIndex > endIndex) {
        return {}; // Return an empty vector if no valid segment is found
    }

    // Create the segmented data vector using the calculated indices
    std::vector<Row> trimmedData(origData.Data.begin() + startIndex, origData.Data.begin() + endIndex + 1);

    return trimmedData;
}*/

DataFrame DataFrame::trimData(DataFrame& origData, int startDayN, int endDayN) {
    DataFrame result;
    for (const auto& row : origData.Data) {
        if (row.timeNumber >= startDayN && row.timeNumber <= endDayN) {
            result.Data.push_back(row);
        }
    }
    return result;
}
/*
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
*/

void DataFrame::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : Data) {
        file << row.toString() << std::endl; // Assuming toString method exists
    }
    file.close();
}

int DataFrame::binarySearchByTimeNumber(size_t referenceTimeNumber) {
    int low = 0;
    int high = Data.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (Data[mid].timeNumber == referenceTimeNumber) {
            return mid; // Found the matching time number, return its index
        } else if (Data[mid].timeNumber < referenceTimeNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Not found
}
DataFrame DataFrame::segmentData(std::string start, std::string end) {
    std::istringstream issStart(start);
    std::string monthS, dayS, timeS;
    issStart >> monthS >> dayS >> timeS;



    std::istringstream issEnd(end);
    std::string monthE, dayE, timeE;
    issEnd >> monthE >> dayE >> timeE;

    Row startTemp = Row(monthS,dayS,timeS,"000.000.000","0000","temp");
    Row endTemp = Row(monthE,dayE,timeE,"000.000.000","0000","temp");
    size_t startSecondsTime = startTemp.timeNumber;
    size_t endSecondsTime = endTemp.timeNumber;



    return DataFrame();
}

size_t DataFrame::size() {


    return this->Data.size();
}

void DataFrame::Print() {
    for(auto data: this->Data){
        std::cout<<data.month<<" "<<data.day<<" "<<data.time<<" "<<data.ip<<data.port<<" "<<data.log<<std::endl;
    }
}

