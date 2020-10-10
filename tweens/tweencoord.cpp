#include "tweencoord.h"

TweenCoord::TweenCoord(ImagePtr image, float final_coord_x, float final_coord_y,
                       float time, std::function <float(float)> tween_curve):
      TweenBase(image, time, tween_curve),
      final_center_x(final_coord_x),
      final_center_y(final_coord_y),
      start_center_x(image->get_center_x()),
      start_center_y(image->get_center_y())
{}

TweenCoord::TweenCoord(ImagePtr image, float start_coord_x, float start_coord_y, float final_coord_x, float final_coord_y,
                       float time, std::function <float(float)> tween_curve):
      TweenBase(image, time, tween_curve),
      final_center_x(final_coord_x),
      final_center_y(final_coord_y),
      start_center_x(start_coord_x),
      start_center_y(start_coord_y)
{}

void TweenCoord::update(float dt)
{
    count_progress(dt);

    auto new_center_x = count_step(start_center_x, final_center_x);
    auto new_center_y = count_step(start_center_y, final_center_y);
    image->set_center(new_center_x, new_center_y);
}

