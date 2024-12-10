#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string email;

public:
    User(const std::string& uname, const std::string& pass, const std::string& mail);
    bool authenticate(const std::string& uname, const std::string& pass) const;
};

#endif // USER_H
