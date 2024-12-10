#include "timer.h"

Timer::Timer() : workDuration(0), breakDuration(0), remainingTime(0), isActive(false), isPaused(false), currentSessionType("work") {}

void Timer::start(int workDuration, int breakDuration) {
    this->workDuration = workDuration * 60;
    this->breakDuration = breakDuration * 60;
    this->remainingTime = this->workDuration;
    this->isActive = true;
    this->isPaused = false;
    this->currentSessionType = "work";
    this->startTime = std::chrono::steady_clock::now();
}

void Timer::pause() {
    if (isActive && !isPaused) {
        remainingTime -= getElapsedTime();
        isPaused = true;
        isActive = false;
    }
}

void Timer::resume() {
    if (isPaused && !isActive) {
        isPaused = false;
        isActive = true;
        startTime = std::chrono::steady_clock::now();
    }
}

void Timer::stop() {
    isActive = false;
    isPaused = false;
    remainingTime = 0;
}

void Timer::reset() {
    workDuration = 0;
    breakDuration = 0;
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

        if (timeLeft <= 0 && currentSessionType == "work") {
            currentSessionType = "break";
            remainingTime = breakDuration;
            startTime = std::chrono::steady_clock::now();
            timeLeft = remainingTime;
        } else if (timeLeft <= 0 && currentSessionType == "break") {
            stop();
            res["status"] = "Completed";
            return res;
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
