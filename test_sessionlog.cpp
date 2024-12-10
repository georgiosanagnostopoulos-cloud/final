#include <cassert>
#include "SessionLog.h"

void testSessionLog() {
    SessionLog log;
    log.logSession("work", 25, "2024-12-05");
    auto history = log.getSessionHistory();
    assert(history.size() == 1);
    assert(history[0].sessionType == "work");
}

int main() {
    testSessionLog();
    std::cout << "SessionLog tests passed!" << std::endl;
    return 0;
}
