#include "crow.h"
#include "timer.h"
#include "session_log.h"
#include "user_manager.h"
#include <ctime>

// Utility function to get the current timestamp
std::string getCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    return std::string(buf);
}

// Global user manager instance
UserManager userManager;

int main() {
    crow::SimpleApp app;

    Timer timer;
    SessionLog sessionLog;

    // POST: User Login
    CROW_ROUTE(app, "/api/login").methods(crow::HTTPMethod::POST)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            std::string username = body["username"].s();
            std::string password = body["password"].s();

            if (userManager.authenticate(username, password)) {
                std::string token = userManager.generateToken(username);
                crow::json::wvalue res;
                res["message"] = "Login successful";
                res["token"] = token;
                return crow::response(200, res);
            } else {
                return crow::response(401, "Invalid username or password");
            }
        });

    // Middleware: Token Validation
    auto validateTokenMiddleware = [](const crow::request& req) -> bool {
        auto token = req.get_header_value("Authorization");
        return userManager.validateToken(token);
    };

    // POST: Start a new timer
    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::POST)(
        [&timer, validateTokenMiddleware](const crow::request& req) {
            if (!validateTokenMiddleware(req)) return crow::response(401, "Unauthorized");

            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            int workDuration = body["workDuration"].i();
            int breakDuration = body["breakDuration"].i();

            timer.start(workDuration, breakDuration);

            crow::json::wvalue res;
            res["status"] = "Timer started";
            res["workDuration"] = workDuration;
            res["breakDuration"] = breakDuration;
            return crow::response(201, res);
        });

    // Other routes (pause, resume, stop, reset, sessions) follow the same pattern:
    // 1. Validate token using `validateTokenMiddleware(req)`.
    // 2. Return `401 Unauthorized` if the token is invalid.

    app.bindaddr("0.0.0.0").port(18080).multithreaded().run();
}
