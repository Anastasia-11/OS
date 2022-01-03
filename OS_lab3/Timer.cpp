//
// Created by ASUS on 15.04.2021.
//

#include "Timer.h"

void Timer::reset() {
    timePoint = clock_t::now();
}

double Timer::elapsed() const {
    return std::chrono::duration_cast<second_t>(clock_t::now() - timePoint).count();
}
