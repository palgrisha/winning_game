#ifndef TWEENQUEUE_H
#define TWEENQUEUE_H
#include "source/tweens/tweenbase.h"
#include "source/tweens/tweenscale.h"
#include "source/tweens/tweencoord.h"
#include <memory>

class TweenQueue
{
    public:
        TweenQueue() = default;

        void add_tween (TweenBasePtr a);
        virtual void update(float dt);
        bool is_empty();
        size_t size();

    protected:
        std::queue <TweenBasePtr> tweens;

};

class CycledQueue : public TweenQueue
{
    public:
        CycledQueue() = default;
    private:
        void update(float dt);
};

typedef std::shared_ptr <TweenQueue> TweenQueuePtr;
typedef std::shared_ptr <CycledQueue> CycledQueuePtr;

#endif // TWEENQUEUE_H
