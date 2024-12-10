#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class ConfigManager {
public:
    static nlohmann::json loadConfig(const std::string& filepath);
    static void saveConfig(const std::string& filepath, const nlohmann::json& data);
    static std::vector<nlohmann::json> loadLogs(const std::string& filepath);
    static void saveLogs(const std::string& filepath, const std::vector<nlohmann::json>& logs);
};

#endif // CONFIGMANAGER_H
