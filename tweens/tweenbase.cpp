#include <math.h>
#include "tweenbase.h"

TweenBase::TweenBase(ImagePtr image, float animation_time, std::function <float(float)> tween_curve):
    image(image),
    progress(0),
    animation_time(animation_time),
    tween_curve(tween_curve)
{
}

bool TweenBase::is_finished()
{
    return progress == 1;
}

void TweenBase::reset()
{
    progress = 0;
}

void TweenBase::count_progress(float dt)
{
    progress += dt / animation_time;
    if (progress < 0)
    {
        progress = 0;
    }
    if (progress > 1)
    {
        progress = 1;
    }
}

float TweenBase::count_step(float start, float stop)
{
    return start + (stop - start) * tween_curve(progress);
}
