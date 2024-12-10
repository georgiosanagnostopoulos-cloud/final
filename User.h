#ifndef USER_H
#define USER_H

#include "Timer.h"
#include "SessionLog.h"
#include <memory>

class User {
private:
    std::string username;
    std::shared_ptr<Timer> timer;
    SessionLog sessionLog;

public:
    User(const std::string& username);

    void startTimer();
    void pauseTimer();
    void resetTimer();
    void logSession(const std::string& sessionType, int duration);
    SessionLog getSessionLog() const;
};

#endif // USER_H
