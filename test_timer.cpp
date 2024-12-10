#include "gtest/gtest.h"
#include "timer.h"
#include "crow.h"

// Test Constructor
TEST(TimerTest, Constructor) {
    Timer timer;
    ASSERT_EQ(timer.getStatus()["status"], "Inactive");  // Default status should be "Inactive"
}

// Test Convert to JSON
TEST(TimerTest, ConvertToJson) {
    Timer timer;
    timer.start(25, 5);  // Start with 25 minutes work and 5 minutes break
    crow::json::wvalue json = timer.getStatus();
    ASSERT_EQ(json["status"].s(), "work");
    ASSERT_EQ(json["remainingTime"].i(), 1500);  // Remaining time for a 25-minute work session (25 * 60 = 1500 seconds)
}

// Test Update from JSON
TEST(TimerTest, UpdateFromJson) {
    Timer timer;
    crow::json::rvalue json_input = crow::json::load(R"({"status": "work", "remainingTime": 1500})");
    timer.updateFromJson(json_input);
    ASSERT_EQ(timer.getStatus()["status"].s(), "work");
    ASSERT_EQ(timer.getStatus()["remainingTime"].i(), 1500);
}

// Test Handling Invalid JSON (missing required field)
TEST(TimerTest, HandleInvalidJson) {
    Timer timer;
    crow::json::rvalue invalid_json = crow::json::load(R"({"status": "work"})");  // Missing remainingTime
    ASSERT_THROW(timer.updateFromJson(invalid_json), std::invalid_argument);
}
