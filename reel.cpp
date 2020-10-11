#include "reel.h"
#include <random>

Reel::Reel(float left, float right, float top, float bottom,
          ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info, TweenManagerPtr tmanager, DrawingManagerPtr drawing_manager) :
    left(left), right(right), top(top), bottom(bottom),
    resource_loader(resource_loader), scene_info(scene_info), tmanager(tmanager), drawing_manager(drawing_manager)
{
    current_speed = boost = final_speed = 0;

    for (int i = 0; i < FIGURES_IN_REEL+2; i++)
    {
        float cur_bottom = bottom + i*(top-bottom) / FIGURES_IN_REEL;
        float cur_top = bottom + (i+1)*(top-bottom) / FIGURES_IN_REEL;

        auto new_image = get_random_figure();
        new_image->set_scale((right-left)/new_image->texture_info->width, (cur_top-cur_bottom)/new_image->texture_info->height);
        new_image->set_center((left+right)/2, (cur_top+cur_bottom)/2);
        images.push_back(new_image);
        drawing_manager->add(new_image);
    }
}

void Reel::stop()
{
    state = State::DELAY;

    auto y_size_of_element = (this->top - this->bottom) / FIGURES_IN_REEL;
    auto bounce_depth = y_size_of_element * 0.75;
    auto distance = get_distance() + bounce_depth;

    for (auto image : images)
    {
        auto start_x = image->get_center_x();
        auto start_y = image->get_center_y();
        auto return_point_y = start_y - distance;
        auto final_y = return_point_y + bounce_depth;
        auto delay_time = distance / current_speed;
        auto return_time = bounce_depth / current_speed * 2;

        auto queue = std::make_shared<TweenQueue>();
        queue->add_tween(std::make_shared <TweenCoord> (image, start_x, return_point_y, delay_time, linear));
        queue->add_tween(std::make_shared <TweenCoord> (image, start_x, return_point_y, start_x, final_y, return_time, sin_out));
        tmanager->add_tween_queue(queue);
        queue_canary = queue;
    }
}

DoubleImagePtr Reel::get_random_figure()
{
    int i = rand(3);

    switch (i)
    {
        case 0:
        {
            return std::make_shared <DoubleImage>(resource_loader->get("star"), scene_info, resource_loader->get("star_win"));
        }

        case 1:
        {
            return std::make_shared <DoubleImage>(resource_loader->get("triangle"), scene_info, resource_loader->get("triangle_win"));
        }

        case 2:
        {
            return std::make_shared <DoubleImage>(resource_loader->get("square"), scene_info, resource_loader->get("square_win"));
        }

        default:
        {
            return std::make_shared <DoubleImage>(resource_loader->get("circle"), scene_info, resource_loader->get("circle_win"));
        }
    }
}

int Reel::rand (int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, max);
    return dist(gen);
}

float Reel::get_distance()
{
    return images[FIGURES_IN_REEL]->get_top_pixel() - top;
}

bool Reel::stopped()
{
    return state == State::IDLE;
}

void Reel::update (float dt)
{
    switch (state)
    {
        case State::IDLE:
        {
            return;
        }

        case State::HASTE:
        {
            current_speed += boost*dt;
            if (current_speed >= final_speed)
            {
                current_speed = final_speed;
                state = State::UNIFORM;
            }

            for (auto image : images)
            {
                image->move_y(current_speed*dt);
            }
            break;
        }

        case State::UNIFORM:
        {
            for (auto image : images)
            {
                image->move_y(current_speed*dt);
            }
            break;
        }

        case State::DELAY:
        {
            if (queue_canary->size() == 1)
            {
                state = State::RETURNING;
            }
        }

        case State::RETURNING:
        {
            if (queue_canary->size() == 0)
            {
                state = State::IDLE;
                correct_images_positions();
            }
        }
    }

    shift_images();
}

void Reel::haste()
{
     final_speed = AVERAGE_SPEED*scene_info->height*(1+0.05*0.2*(rand(10)-5));  //average +- 5%
     current_speed = 0;
     boost = (final_speed - current_speed) / TIME_FOR_SPEED_INCREASE;
     state = State::HASTE;
}

void Reel::correct_images_positions()
{
    float ysize = images.at(0)->get_top_pixel()-images.at(0)->get_bottom_pixel();
    float zero_center_y = images.at(0)->get_center_y();

    for (size_t i = 1; i < images.size(); i++)
    {
        images.at(i)->set_center_y(zero_center_y + ysize*i);
    }
}

void Reel::shift_images()
{
    while (images.at(0)->get_top_pixel() < bottom)
    {
        drawing_manager->remove(images.at(0));
        for (int i = 0; i < FIGURES_IN_REEL+1; i++)
        {
            images.at(i) = images.at(i+1);
        }

        float ysize = (top-bottom)/FIGURES_IN_REEL;
        float cur_bottom = images.at(FIGURES_IN_REEL)->get_top_pixel();
        float cur_top = images.at(FIGURES_IN_REEL)->get_top_pixel() + ysize;

        images.pop_back();

        auto new_image = get_random_figure();
        new_image->set_scale((right-left) / new_image->texture_info->width,
                             (cur_top-cur_bottom) / new_image->texture_info->height);
        new_image->set_center((left+right)/2, (cur_top+cur_bottom)/2);
        images.push_back(new_image);
        drawing_manager->add(new_image);
    }
}

std::vector <DoubleImagePtr> Reel::get_final_set()
{
    std::vector <DoubleImagePtr> set;

    for (auto i = 0; i < FIGURES_IN_REEL; i++)
    {
        set.push_back(images.at(i));
    }

    return set;
}
