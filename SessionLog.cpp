#include "SessionLog.h"

void SessionLog::logSession(const std::string& sessionType, int duration, const std::string& timestamp) {
    logs.push_back({{"type", sessionType}, {"duration", duration}, {"timestamp", timestamp}});
}

std::vector<nlohmann::json> SessionLog::getSessionHistory() const {
    return logs;
}
