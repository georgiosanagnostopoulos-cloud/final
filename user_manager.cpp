#include "user_manager.h"
#include <random>

UserManager::UserManager() {
    // Add predefined users
    users["admin"] = "password123";
    users["user"] = "userpass";
}

bool UserManager::authenticate(const std::string& username, const std::string& password) {
    return users.find(username) != users.end() && users[username] == password;
}

std::string UserManager::generateToken(const std::string& username) {
    // Generate a random token
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string token;
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    for (int i = 0; i < 16; ++i) {
        token += characters[distribution(generator)];
    }

    // Store the token for the user
    tokens[username] = token;
    return token;
}

bool UserManager::validateToken(const std::string& token) {
    for (const auto& pair : tokens) {
        if (pair.second == token) {
            return true; // Token is valid
        }
    }
    return false;
}
