#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <unordered_map>

class UserManager {
private:
    std::unordered_map<std::string, std::string> users;  // username -> password
    std::unordered_map<std::string, std::string> tokens; // username -> token

public:
    UserManager();
    bool authenticate(const std::string& username, const std::string& password);
    std::string generateToken(const std::string& username);
    bool validateToken(const std::string& token);
};

#endif
