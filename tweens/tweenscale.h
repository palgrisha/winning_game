#ifndef TWEENSCALE_H
#define TWEENSCALE_H
#include "tweens/tweenbase.h"

class TweenScale : public TweenBase
{
    public:
        TweenScale(ImagePtr figure, float final_scale_x, float final_scale_y,
                   float time, std::function <float(float)> tween_curve);
        TweenScale(ImagePtr image, float start_scale_x, float start_scale_y, float final_scale_x, float final_scale_y,
                   float time, std::function <float(float)> tween_curve);
        void update(float dt) override;

    private :
        float final_scale_x, final_scale_y;
        float start_scale_x, start_scale_y;
};

typedef std::shared_ptr <TweenScale> TweenScalePtr;
#endif // TWEENSCALE_H
