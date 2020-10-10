#include "tweenmanager.h"

void TweenManager::add_tween_queue(std::shared_ptr <TweenQueue> a)
{
    tweens.push_back(a);
}

void TweenManager::update(float dt)
{
    for (auto tween_queue : tweens)
    {
        tween_queue->update(dt);
    }
}

void TweenManager::remove_empty_queues()
{
    for (auto it = tweens.begin(); it < tweens.end();)
    {
        if ((*it)->is_empty())
        {
            tweens.erase(it);
        }
        else
        {
            it++;
        }
    }
}

bool TweenManager::remove_tween_queue(TweenQueuePtr q)
{
    for (auto it = tweens.begin(); it < tweens.end();)
    {
        if (*it == q)
        {
            tweens.erase(it);
            return true;
        }
        else
        {
            it++;
        }
    }
    return false;
}
