#include "tweenqueue.h"

void TweenQueue::add_tween (std::shared_ptr <TweenBase> a)
{
    tweens.push(a);
}

void TweenQueue::update(float dt)
{
    if (tweens.empty())
        return;
    tweens.front()->update(dt);
    if (tweens.front()->is_finished())
    {
        tweens.pop();
    }
}

bool TweenQueue::is_empty()
{
    if (tweens.empty())
    {
        return true;
    }
    return false;
}

size_t TweenQueue::size()
{
    return tweens.size();
}

void CycledQueue::update(float dt)
{
    tweens.front()->update(dt);
    if (tweens.front()->is_finished())
    {
        auto temp = tweens.front();
        temp->reset();
        tweens.pop();
        tweens.push(temp);
    }
}
