//
// Created by ASUS on 15.04.2021.
//

#ifndef OS_LAB3_TIMER_H
#define OS_LAB3_TIMER_H

#include <chrono>

class Timer {
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> timePoint;

public:
    Timer() : timePoint(clock_t::now()) {}

    void reset();
    double elapsed() const;
};


#endif //OS_LAB3_TIMER_H
