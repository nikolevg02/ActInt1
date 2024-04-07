
#include "Row.h"
#include <iostream>
#include <string>
#include <sstream>
int main(){




        // The time string
        std::string time = "18:43:58";

        // Lambda to process the time string
        auto convertToSeconds = [](const std::string& time) -> int {
            std::istringstream stream(time);
            std::string segment;
            int hours = 0, minutes = 0, seconds = 0, totalSeconds = 0;

            // Get hours
            std::getline(stream, segment, ':');
            hours = std::stoi(segment);

            // Get minutes
            std::getline(stream, segment, ':');
            minutes = std::stoi(segment);

            // Get seconds
            std::getline(stream, segment);
            seconds = std::stoi(segment);

            // Convert everything to seconds and sum it up
            totalSeconds = hours * 3600 + minutes * 60 + seconds;
            std::cout<< hours<<std::endl;
            std::cout<< minutes<<std::endl;
            std::cout<< seconds<<std::endl;

            return totalSeconds;
        };

        // Use the lambda and print the result
        int totalSeconds = convertToSeconds(time);
        std::cout << "Total seconds: " << totalSeconds << std::endl;


        return 0;
    }
