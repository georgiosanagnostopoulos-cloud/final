#include "gtest/gtest.h"
#include "session_log.h"
#include "timer.h"

// Test Constructor and Initial State
TEST(SessionLogTest, Constructor) {
    SessionLog log;
    ASSERT_EQ(log.getLogs().size(), 0);  // No sessions should be logged initially
}

// Test logSession Method
TEST(SessionLogTest, LogSession) {
    SessionLog log;
    Session session = {"work", 1500, "2024-12-10 10:00:00", "2024-12-10 10:25:00"};
    log.logSession(session);
    ASSERT_EQ(log.getLogs().size(), 1);  // One session should be logged
}

// Test getTotalWorkSessions Method
TEST(SessionLogTest, GetTotalWorkSessions) {
    SessionLog log;
    Session work_session = {"work", 1500, "2024-12-10 10:00:00", "2024-12-10 10:25:00"};
    log.logSession(work_session);
    ASSERT_EQ(log.getTotalWorkSessions(), 1);
}

// Test getLongestSession Method
TEST(SessionLogTest, GetLongestSession) {
    SessionLog log;
    Session session1 = {"work", 1500, "2024-12-10 10:00:00", "2024-12-10 10:25:00"};
    Session session2 = {"work", 1800, "2024-12-10 11:00:00", "2024-12-10 11:30:00"};
    log.logSession(session1);
    log.logSession(session2);
    ASSERT_EQ(log.getLongestSession().duration, 1800);  // Longest session duration should be 1800
}

// Test Clear Logs Method
TEST(SessionLogTest, ClearLogs) {
    SessionLog log;
    Session session = {"work", 1500, "2024-12-10 10:00:00", "2024-12-10 10:25:00"};
    log.logSession(session);
    log.clearLogs();
    ASSERT_EQ(log.getLogs().size(), 0);  // Logs should be cleared
}
