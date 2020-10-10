#include "timer.h"

Timer::Timer(float time, std::function <void(void)> call_back):
    time(time),_callback(call_back)
{    
}

void Timer::update(float dt)
{
    time -= dt;
    if (time <= 0)
    {
        _callback();
    }
}

bool Timer::finished()
{
    return time <= 0;
}
