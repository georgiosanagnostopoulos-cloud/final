#ifndef SESSIONLOG_H
#define SESSIONLOG_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

struct Session {
    std::string sessionType; // "work" or "break"
    int duration;            // in minutes
    std::string timestamp;
};

class SessionLog {
private:
    std::vector<nlohmann::json> logs;

public:
    void logSession(const std::string& sessionType, int duration, const std::string& timestamp);
    std::vector<nlohmann::json> getSessionHistory() const;
};

#endif // SESSIONLOG_H
