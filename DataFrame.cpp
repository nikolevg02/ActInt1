
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

    // Logic remains the same, but it operates on `this->Data`
    int maxDigitCount = mostDigits(Data);

    for (int k = 0; k < maxDigitCount; ++k) {
        std::vector<std::vector<Row>> buckets(10);
        for (auto &row: Data) {
            int digit = getDigit(row.timeNumber, k);
            buckets[digit].push_back(row);
        }
        Data = vectorConcat(buckets);
    }
}
