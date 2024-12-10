#include <iostream>
#include "User.h"
#include "ConfigManager.h"

int main() {
    try {
        auto config = ConfigManager::loadConfig("data/config.json");
        User user(config["username"]);
        
        std::cout << "Welcome, " << config["username"] << "!" << std::endl;
        user.startTimer();
        user.logSession("work", config["workDuration"]);
        
        ConfigManager::saveLogs("data/sessions.json", user.getSessionLog().getSessionHistory());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
