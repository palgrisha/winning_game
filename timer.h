#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <memory>

class Timer
{
    public:
        Timer(float time, std::function <void(void)> call_back);
        bool finished();
        void update(float dt);
    private:
        float time;
        std::function <void (void)> _callback;

};

typedef std::shared_ptr <Timer> TimerPtr;

#endif // TIMER_H
