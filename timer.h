#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>
#include "crow.h"

class Timer {
private:
    int workDuration;    // Duration of work session in seconds
    int breakDuration;   // Duration of break session in seconds
    int remainingTime;   // Remaining time in seconds
    bool isActive;
    bool isPaused;
    std::string currentSessionType; // "work" or "break"
    std::chrono::time_point<std::chrono::steady_clock> startTime;

public:
    Timer();
    void start(int workDuration, int breakDuration);
    void pause();
    void resume();
    void stop();
    void reset();
    crow::json::wvalue getStatus();
    int getElapsedTime();
    std::string getSessionType();
};

#endif
