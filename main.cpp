#include "crow.h"
#include "timer.h"
#include "session_log.h"
#include "notification.h"
#include <ctime>

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

    // Add a sample notification for testing
    notificationManager.addNotification("System", "Server started successfully");

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

    // PUT: Pause or Resume the timer
    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::PUT)(
        [&timer](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            std::string action = body["action"].s();
            if (action == "pause") {
                timer.pause();
                notificationManager.addNotification("Timer", "Timer paused successfully");
                return crow::response(200, "Timer paused");
            } else if (action == "resume") {
                timer.resume();
                notificationManager.addNotification("Timer", "Timer resumed successfully");
                return crow::response(200, "Timer resumed");
            } else {
                return crow::response(400, "Invalid action");
            }
        });

    // PUT: Stop the timer
    CROW_ROUTE(app, "/api/timers/stop").methods(crow::HTTPMethod::PUT)(
        [&timer, &sessionLog]() {
            Session session;
            session.sessionType = timer.getSessionType();
            session.duration = timer.getElapsedTime();
            session.startTime = "N/A";
            session.endTime = getCurrentTimestamp();

            sessionLog.logSession(session);
            timer.stop();
            notificationManager.addNotification("Timer", "Timer stopped and session logged");

            return crow::response(200, "Timer stopped and session logged");
        });

    // DELETE: Reset the timer
    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::DELETE)(
        [&timer]() {
            timer.reset();
            notificationManager.addNotification("Timer", "Timer reset successfully");
            return crow::response(200, "Timer reset");
        });

    // GET: Retrieve the timer status
    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::GET)(
        [&timer]() {
            return crow::response(timer.getStatus());
        });

    // GET: Retrieve session logs
    CROW_ROUTE(app, "/api/sessions").methods(crow::HTTPMethod::GET)(
        [&sessionLog]() {
            auto logs = sessionLog.getLogs();
            crow::json::wvalue res;
            auto& sessionsArray = res["sessions"];
            sessionsArray = crow::json::wvalue::list();

            for (const auto& session : logs) {
                crow::json::wvalue s;
                s["sessionType"] = session.sessionType;
                s["duration"] = session.duration;
                s["startTime"] = session.startTime;
                s["endTime"] = session.endTime;
                sessionsArray[sessionsArray.size()] = std::move(s);
            }
            return crow::response(200, res);
        });

    // GET: Retrieve notifications
    CROW_ROUTE(app, "/api/notifications").methods(crow::HTTPMethod::GET)(
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

    // PUT: Mark all notifications as read
    CROW_ROUTE(app, "/api/notifications/markAsRead").methods(crow::HTTPMethod::PUT)(
        []() {
            notificationManager.markAllAsRead();
            return crow::response(200, "All notifications marked as read");
        });

    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();
}
