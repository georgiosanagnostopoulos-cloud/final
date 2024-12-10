#ifndef SESSION_LOG_H
#define SESSION_LOG_H

#include <vector>
#include <string>
#include <mutex>

struct Session {
    std::string sessionType;
    int duration;
    std::string startTime;
    std::string endTime;
};

class SessionLog {
private:
    std::vector<Session> logs;
    std::mutex logMutex;

public:
    void logSession(const Session& session);
    std::vector<Session> getLogs();
    int getTotalSessions(); // Add this declaration
};

#endif
