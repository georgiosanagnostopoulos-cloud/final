#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>
#include "crow.h"

class Timer {
private:
    int workDuration;
    int breakDuration;
    int remainingTime;
    bool isActive;
    bool isPaused;
    std::string currentSessionType;
    std::string timerName; // New attribute for naming the timer
    int completedSessions;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

public:
    Timer();
    void start(int workDuration, int breakDuration);
    void pause();
    void resume();
    void stop();
    void reset();
    void setName(const std::string& name);
    void incrementCompletedSessions();
    int getCompletedSessions() const;
    crow::json::wvalue getStatus();
    int getElapsedTime();
    std::string getSessionType();
};

#endif
