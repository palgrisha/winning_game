#include "actiontween.h"

ActionTween::ActionTween(ImagePtr figure, float final_scale_x, float final_scale_y,
                         float time, std::function <float(float)> tween_curve, std::function <void()> action):

    TweenScale(figure, final_scale_x, final_scale_y, time, tween_curve),
    action(action)
{
}

ActionTween::ActionTween(ImagePtr figure, float start_scale_x, float start_scale_y, float final_scale_x, float final_scale_y,
                         float time, std::function <float(float)> tween_curve, std::function <void()> action):

    TweenScale(figure, start_scale_x, start_scale_y, final_scale_x, final_scale_y, time, tween_curve),
    action(action)
{
}

void ActionTween::update(float dt)
{
    TweenScale::update(dt);
    if (is_finished())
        action();
}
