#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <cstdint>

class Timer {
    public:
        using Nanos = std::chrono::nanoseconds;
        using Micros = std::chrono::microseconds;
        using Millis = std::chrono::milliseconds;
        using Seconds = std::chrono::seconds;
        using Minutes = std::chrono::minutes;
        using Hours = std::chrono::hours;

        Timer(){
            startTime = currentTime = lastTime = std::chrono::steady_clock::now();
        }
        void Restart(){
            startTime = std::chrono::steady_clock::now();
        }

        template <typename T>
        uint64_t click(){
            currentTime = std::chrono::steady_clock::now();
            uint64_t elapsedTime = std::chrono::duration_cast<T>(currentTime - lastTime).count();
            lastTime = currentTime;
            return elapsedTime;
        }

        template <typename T>
        uint64_t glance() {
            currentTime = std::chrono::steady_clock::now();
            uint64_t elapsedTime = std::chrono::duration_cast<T>(currentTime - lastTime).count();
            return elapsedTime;
        }
    
    private:
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point currentTime;
        std::chrono::steady_clock::time_point lastTime;



};

#endif  // TIMER_H
