#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H
#include <vector>
#include "source/timer.h"

class TimerManager
{
    public:
        TimerManager() = default;

        void add_timer(TimerPtr timer);
        void update(float dt);
        bool remove_timer(TimerPtr q);
        void remove_empty_timers();

    private:
        std::vector <TimerPtr> timers;
};

typedef std::shared_ptr <TimerManager> TimerManagerPtr;

#endif // TIMERMANAGER_H
