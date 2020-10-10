#include "timermanager.h"

void TimerManager::add_timer(TimerPtr a)
{
    timers.push_back(a);
}

void TimerManager::update(float dt)
{
    for (auto timer : timers)
    {
        timer->update(dt);
    }
}

void TimerManager::remove_empty_timers()
{
    for (auto it = timers.begin(); it < timers.end();)
    {
        if ((*it)->finished())
        {
            timers.erase(it);
        }
        else
        {
            it++;
        }
    }
}

bool TimerManager::remove_timer(TimerPtr timer)
{
    for (auto it = timers.begin(); it < timers.end();)
    {
        if (*it == timer)
        {
            timers.erase(it);
            return true;
        }
        else
        {
            it++;
        }
    }
    return false;
}

