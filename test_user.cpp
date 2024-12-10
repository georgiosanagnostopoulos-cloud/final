#include <cassert>
#include "User.h"

void testUser() {
    User user("John");
    user.startTimer();
    user.logSession("work", 25);
    auto log = user.getSessionLog().getSessionHistory();
    assert(log.size() == 1);
    assert(log[0].sessionType == "work");
}

int main() {
    testUser();
    std::cout << "User tests passed!" << std::endl;
    return 0;
}
