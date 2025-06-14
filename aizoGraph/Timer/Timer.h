#pragma once
#include <chrono>

class Timer {
public:
    Timer(); // Initialize and prepare to start.
    void reset(); // Reset timer.
    int start(); // Start timer.
    int stop(); // Stop timer.
    int result(); // Return elapsed time [ms].

private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point stopTime;
};
