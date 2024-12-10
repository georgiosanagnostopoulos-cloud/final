#include "crow.h"
#include "timer.h"
#include "session_log.h"
#include "notification.h"
#include <ctime>
#include <iostream>

// Utility function to get the current timestamp
std::string getCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    return std::string(buf);
}

// Global Instances
NotificationManager notificationManager;

int main() {
    crow::SimpleApp app;

    Timer timer;
    SessionLog sessionLog;

    // POST: Start a new timer
    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::POST)(
        [&timer](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            int workDuration = body["workDuration"].i();
            int breakDuration = body["breakDuration"].i();

            timer.start(workDuration, breakDuration);
            notificationManager.addNotification("Timer", "Timer started successfully");

            crow::json::wvalue res;
            res["status"] = "Timer started";
            res["workDuration"] = workDuration;
            res["breakDuration"] = breakDuration;
            return crow::response(201, res);
        });

    // POST: Add a notification from a JSON payload (Updated Path)
    CROW_ROUTE(app, "/api/notification").methods(crow::HTTPMethod::POST)(
        [](const crow::request& req) {
            extern NotificationManager notificationManager;

            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            std::string type = body["type"].s();
            std::string message = body["message"].s();

            // Add the notification
            notificationManager.addNotification(type, message);

            // Print the notification to the console
            std::cout << "Notification Added: " << std::endl;
            std::cout << "Type: " << type << std::endl;
            std::cout << "Message: " << message << std::endl;

            crow::json::wvalue res;
            res["status"] = "Notification added successfully";
            return crow::response(201, res);
        });

    // GET: Retrieve notifications (Updated Path)
    CROW_ROUTE(app, "/api/notification").methods(crow::HTTPMethod::GET)(
        []() {
            auto notifications = notificationManager.getNotifications();
            crow::json::wvalue res;
            auto& notifArray = res["notifications"];
            notifArray = crow::json::wvalue::list();

            for (const auto& notif : notifications) {
                crow::json::wvalue n;
                n["id"] = notif.id;
                n["type"] = notif.type;
                n["message"] = notif.message;
                n["timestamp"] = notif.timestamp;
                n["isRead"] = notif.isRead;
                notifArray[notifArray.size()] = std::move(n);
            }
            return crow::response(200, res);
        });

    // PUT: Mark all notifications as read (Updated Path)
    CROW_ROUTE(app, "/api/notification/markAsRead").methods(crow::HTTPMethod::PUT)(
        []() {
            notificationManager.markAllAsRead();
            return crow::response(200, "All notifications marked as read");
        });

    app.bindaddr("0.0.0.0").port(17080).multithreaded().run();
}
