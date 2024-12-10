#include <cassert>
#include "Timer.h"

void testTimer() {
    Timer timer(25, 5);
    timer.start();
    assert(timer.getStatus() == "Running");

    timer.pause();
    assert(timer.getStatus() == "Paused");

    timer.reset();
    assert(timer.getStatus() == "Idle");
}

int main() {
    testTimer();
    std::cout << "Timer tests passed!" << std::endl;
    return 0;
}
