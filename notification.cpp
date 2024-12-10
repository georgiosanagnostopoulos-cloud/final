#include "notification.h"
#include <ctime>

// Constructor for Notification
Notification::Notification(int id, const std::string& type, const std::string& message)
    : id(id), type(type), message(message), isRead(false) {
    // Generate timestamp
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    timestamp = std::string(buf);
}

// Mark Notification as Read
void Notification::markAsRead() {
    isRead = true;
}

// Add a Notification
void NotificationManager::addNotification(const std::string& type, const std::string& message) {
    notifications.emplace_back(nextId++, type, message);
}

// Get all Notifications
std::vector<Notification> NotificationManager::getNotifications() const {
    return notifications;
}

// Mark all Notifications as Read
void NotificationManager::markAllAsRead() {
    for (auto& notification : notifications) {
        notification.markAsRead();
    }
}
