#include "tweenscale.h"

TweenScale::TweenScale(ImagePtr image, float final_scale_x, float final_scale_y,
                       float time, std::function <float(float)> tween_curve):
      TweenBase(image, time, tween_curve),
      final_scale_x(final_scale_x),
      final_scale_y(final_scale_y),
      start_scale_x(image->get_scale_x()),
      start_scale_y(image->get_scale_y())
{
}

TweenScale::TweenScale(ImagePtr image, float start_scale_x, float start_scale_y, float final_scale_x, float final_scale_y,
                       float time, std::function <float(float)> tween_curve):
      TweenBase(image, time, tween_curve),
      final_scale_x(final_scale_x),
      final_scale_y(final_scale_y),
      start_scale_x(start_scale_x),
      start_scale_y(start_scale_y)
{
}

void TweenScale::update(float dt)
{
    count_progress(dt);

    auto new_scale_x = count_step(start_scale_x, final_scale_x);
    auto new_scale_y = count_step(start_scale_y, final_scale_y);
    image->set_scale(new_scale_x, new_scale_y);
}
