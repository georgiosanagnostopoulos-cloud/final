#include "gtest/gtest.h"
#include "notification.h"

// Test Constructor
TEST(NotificationTest, Constructor) {
    Notification notification(1, "Timer", "Timer started successfully!");
    ASSERT_EQ(notification.type, "Timer");
    ASSERT_EQ(notification.message, "Timer started successfully!");
    ASSERT_FALSE(notification.isRead);  // New notifications should not be read
}

// Test Mark As Read
TEST(NotificationTest, MarkAsRead) {
    Notification notification(1, "Timer", "Timer started successfully!");
    notification.markAsRead();
    ASSERT_TRUE(notification.isRead);  // Notification should be marked as read
}

// Test Update Message
TEST(NotificationTest, UpdateMessage) {
    Notification notification(1, "Timer", "Timer started successfully!");
    notification.updateMessage("Timer paused");
    ASSERT_EQ(notification.message, "Timer paused");  // Message should be updated
}

// Test IsUnread Method
TEST(NotificationTest, IsUnread) {
    Notification notification(1, "Timer", "Timer started successfully!");
    ASSERT_TRUE(notification.isUnread());  // It should be unread initially
    notification.markAsRead();
    ASSERT_FALSE(notification.isUnread());  // After marking as read, it should be false
}
