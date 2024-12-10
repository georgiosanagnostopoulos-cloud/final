#ifndef TIMER_H
#define TIMER_H

#include <string>

class Timer {
private:
    int workDuration;
    int breakDuration;
    std::string status; // "Idle", "Running", "Paused", "Completed"
    int remainingTime;

public:
    Timer(int workDuration = 25, int breakDuration = 5);

    void start();
    void pause();
    void reset();
    std::string getStatus() const;
    int getRemainingTime() const;
    void updateDurations(int newWorkDuration, int newBreakDuration);
};

#endif // TIMER_H
