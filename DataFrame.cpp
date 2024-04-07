
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
static void radixSort(std::vector<Row>& data) {
    if (data.empty()) return;

    // Find the max digit count
    int maxDigitCount = mostDigits(data);

    // Perform radix sort
    for (int k = 0; k < maxDigitCount; ++k) {
        std::vector<std::vector<Row>> buckets(10);
        for (auto& row : data) {
            int digit = getDigit(row.dayNumber, k);
            buckets[digit].push_back(row);
        }
        data = vectorConcat(buckets);
    }
}


static int getDigit(int num, int place) {
    return std::abs(num) / static_cast<int>(std::pow(10, place)) % 10;
}

static int countDigits(int num) {
    if (num == 0) return 1;
    return std::floor(std::log10(std::abs(num))) + 1;
}

static int mostDigits(const std::vector<Row>& data) {
    int maxDigits = 0;
    for (const auto& row : data) {
        maxDigits = std::max(maxDigits, countDigits(row.timeNumber));
    }
    return maxDigits;
}

static std::vector<Row> vectorConcat(const std::vector<std::vector<Row>>& buckets) {
    std::vector<Row> result;
    for (const auto& bucket : buckets) {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }
    return result;
}

