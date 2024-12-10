#include "session_log.h"

void SessionLog::logSession(const Session& session) {
    std::lock_guard<std::mutex> lock(logMutex);
    logs.push_back(session);
}

std::vector<Session> SessionLog::getLogs() {
    std::lock_guard<std::mutex> lock(logMutex);
    return logs;
}

int SessionLog::getTotalSessions() { // Definition of the method
    std::lock_guard<std::mutex> lock(logMutex);
    return logs.size();
}
