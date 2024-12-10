#include "ConfigManager.h"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

json ConfigManager::loadConfig(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open config file.");
    }
    json config;
    file >> config;
    return config;
}

void ConfigManager::saveConfig(const std::string& filepath, const json& data) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to save config file.");
    }
    file << data.dump(4);
}

std::vector<json> ConfigManager::loadLogs(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open logs file.");
    }
    json logs;
    file >> logs;
    return logs.get<std::vector<json>>();
}

void ConfigManager::saveLogs(const std::string& filepath, const std::vector<json>& logs) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to save logs file.");
    }
    file << json(logs).dump(4);
}
