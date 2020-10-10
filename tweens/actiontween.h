#ifndef ACTIONTWEEN_H
#define ACTIONTWEEN_H
#include "tweenscale.h"
#include "functional"

class ActionTween : public TweenScale
{
public:
    ActionTween(ImagePtr figure, float final_scale_x, float final_scale_y,
               float time, std::function <float(float)> tween_curve, std::function <void()> action);
    ActionTween(ImagePtr image, float start_scale_x, float start_scale_y, float final_scale_x, float final_scale_y,
               float time, std::function <float(float)> tween_curve, std::function <void()> action);
    void update(float dt) override;
private:
    std::function <void()> action;
};

#endif // ACTIONTWEEN_H
