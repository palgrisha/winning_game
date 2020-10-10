#ifndef TWEEN_H
#define TWEEN_H
#include "image.h"
#include <queue>
#include <functional>

class TweenBase
{
    public:       
        virtual void update(float dt)=0;
        bool is_finished();
        void reset();
    protected :
        TweenBase(ImagePtr image, float animation_time, std::function <float(float)> tween_curve);
        ImagePtr image;
        float progress;
        float animation_time;
        float count_step(float start, float stop);
        void count_progress(float dt);
        std::function <float (float)> tween_curve;

};

typedef std::shared_ptr <TweenBase> TweenBasePtr;

#endif // TWEEN_H
