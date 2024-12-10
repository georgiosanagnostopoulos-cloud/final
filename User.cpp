#include "User.h"

User::User(const std::string& uname, const std::string& pass, const std::string& mail)
    : username(uname), password(pass), email(mail) {}

bool User::authenticate(const std::string& uname, const std::string& pass) const {
    return username == uname && password == pass;
}
