#include "timer.h"

Timer::Timer()
    : totalWorkDuration(0), totalBreakDuration(0), remainingTime(0),
      isActive(false), isPaused(false), currentSessionType("work") {}

void Timer::start(int workDuration, int breakDuration) {
    totalWorkDuration = workDuration * 60;     // Convert minutes to seconds
    totalBreakDuration = breakDuration * 60;   // Convert minutes to seconds
    remainingTime = totalWorkDuration;
    isActive = true;
    isPaused = false;
    currentSessionType = "work";
    startTime = std::chrono::steady_clock::now();
}

void Timer::pause() {
    if (isActive && !isPaused) {
        remainingTime -= getElapsedTime();
        isPaused = true;
        isActive = false;
    }
}

void Timer::resume() {
    if (!isActive && isPaused) {
        isPaused = false;
        isActive = true;
        startTime = std::chrono::steady_clock::now();
    }
}

void Timer::stop() {
    if (isActive || isPaused) {
        remainingTime = 0;
        isActive = false;
        isPaused = false;
    }
}

void Timer::reset() {
    totalWorkDuration = 0;
    totalBreakDuration = 0;
    remainingTime = 0;
    isActive = false;
    isPaused = false;
    currentSessionType = "work";
}

crow::json::wvalue Timer::getStatus() {
    crow::json::wvalue res;
    if (!isActive && !isPaused) {
        res["status"] = "Inactive";
        res["remainingTime"] = 0;
    } else if (isPaused) {
        res["status"] = "Paused";
        res["remainingTime"] = remainingTime;
    } else {
        int elapsedTime = getElapsedTime();
        int timeLeft = remainingTime - elapsedTime;
        if (timeLeft <= 0) {
            // Switch to break session
            currentSessionType = "break";
            remainingTime = totalBreakDuration;
            startTime = std::chrono::steady_clock::now();
            timeLeft = remainingTime;
        }
        res["status"] = currentSessionType;
        res["remainingTime"] = timeLeft;
    }
    return res;
}

int Timer::getElapsedTime() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
}

std::string Timer::getSessionType() {
    return currentSessionType;
}
