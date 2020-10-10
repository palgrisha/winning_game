#ifndef TWEENMANAGER_H
#define TWEENMANAGER_H
#include <vector>
#include "source/tweens/tweenqueue.h"

class TweenManager
{
public:
    TweenManager() = default;
    void add_tween_queue(TweenQueuePtr q);
    void update(float dt);
    bool remove_tween_queue(TweenQueuePtr q);
    void remove_empty_queues();

private:
    std::vector <std::shared_ptr <TweenQueue> > tweens;
};

typedef std::shared_ptr <TweenManager> TweenManagerPtr;

#endif // TWEENMANAGER_H
