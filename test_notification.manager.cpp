#include "gtest/gtest.h"
#include "notification.h"
#include "crow.h"

// Test Add Notification
TEST(NotificationManagerTest, AddNotification) {
    NotificationManager manager;
    manager.addNotification("Timer", "Timer started successfully!");
    auto notifications = manager.getNotifications();
    ASSERT_EQ(notifications.size(), 1);
    ASSERT_EQ(notifications[0].type, "Timer");
    ASSERT_EQ(notifications[0].message, "Timer started successfully!");
}

// Test Mark All As Read
TEST(NotificationManagerTest, MarkAllAsRead) {
    NotificationManager manager;
    manager.addNotification("Timer", "Timer started successfully!");
    manager.markAllAsRead();
    auto notifications = manager.getNotifications();
    ASSERT_EQ(notifications[0].isRead, true);  // The notification should be marked as read
}

// Test Get Unread Count
TEST(NotificationManagerTest, GetUnreadCount) {
    NotificationManager manager;
    manager.addNotification("Timer", "Timer started successfully!");
    ASSERT_EQ(manager.getUnreadCount(), 1);  // One unread notification
}

// Test Delete Notification
TEST(NotificationManagerTest, DeleteNotification) {
    NotificationManager manager;
    manager.addNotification("Timer", "Timer started successfully!");
    auto notifications = manager.getNotifications();
    manager.deleteNotification(notifications[0].id);
    ASSERT_EQ(manager.getNotifications().size(), 0);  // No notifications left
}

// Test Add New Notification Type
TEST(NotificationManagerTest, AddNotificationType) {
    NotificationManager manager;
    manager.addNotificationType("Warning");
    auto types = manager.getNotificationTypes();
    ASSERT_TRUE(types.find("Warning") != types.end());  // "Warning" type should be present
}
