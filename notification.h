#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <vector>

class Notification {
public:
    int id;
    std::string type;
    std::string message;
    std::string timestamp;
    bool isRead;

    Notification(int id, const std::string& type, const std::string& message);
    void markAsRead();
};

class NotificationManager {
private:
    std::vector<Notification> notifications;
    int nextId = 1;

public:
    void addNotification(const std::string& type, const std::string& message);
    std::vector<Notification> getNotifications() const;
    void markAllAsRead();
};

#endif
