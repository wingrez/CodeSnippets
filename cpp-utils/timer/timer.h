//
// Created by Wingrez on 2021/8/15.
//

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace wingrez {
namespace unit {
    typedef std::ratio<1, 1000000000> ns;
    typedef std::ratio<1, 1000000>    us;
    typedef std::ratio<1, 1000>       ms;
    typedef std::ratio<1, 1>          s;
    typedef std::ratio<60, 1>         min;
    typedef std::ratio<3600, 1>       hour;
    typedef std::ratio<86400, 1>      day;
}

class Timer {
public:
    Timer() = delete;
    ~Timer() = delete;
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    static void reset() {
        _startTime = std::chrono::steady_clock::now();
        _lastTime = std::chrono::steady_clock::now();
    }

    template<typename T>
    static double getElapsedTime() {
        std::chrono::time_point curTime = std::chrono::steady_clock::now();
        double duration = std::chrono::duration<double, T>(curTime - _startTime).count();
        return duration;
    }

    template<typename T>
    static double getSpanTime() {
        std::chrono::time_point curTime = std::chrono::steady_clock::now();
        double duration = std::chrono::duration<double, T>(curTime - _lastTime).count();
        _lastTime = curTime;
        return duration;
    }

private:
    static std::chrono::steady_clock::time_point _startTime;
    static std::chrono::steady_clock::time_point _lastTime;
};

std::chrono::steady_clock::time_point Timer::_startTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point Timer::_lastTime = std::chrono::steady_clock::now();

}

#endif //TIMER_H
