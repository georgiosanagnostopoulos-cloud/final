#include "User.h"

User::User(const std::string& username) : username(username), timer(std::make_shared<Timer>()) {}

void User::startTimer() {
    timer->start();
}

void User::pauseTimer() {
    timer->pause();
}

void User::resetTimer() {
    timer->reset();
}

void User::logSession(const std::string& sessionType, int duration) {
    sessionLog.logSession(sessionType, duration, "2024-12-05"); // Mock timestamp
}

SessionLog User::getSessionLog() const {
    return sessionLog;
}
