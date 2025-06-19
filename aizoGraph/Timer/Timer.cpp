#include "C:\Users\KatarzynaNowomiejska\Desktop\aizo_dwa\aizoGraph\Timer\Timer.h"
#include <chrono>

Timer::Timer() {
        start();
    }

int Timer::start() {
        startTime = std::chrono::steady_clock::now();
        return 0;
    }

int Timer::stop() {
        stopTime = std::chrono::steady_clock::now();
        return 0;
    };

int Timer::result() {
    std::chrono::duration<long long, std::milli> duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
    return duration.count();
}
