#include "imagebutton.h"
#include "source/tweens/tweenscale.h"

ImageButton::ImageButton(ImagePtr image, TweenManagerPtr tmanager, int key) :
    image(image),
    tmanager(tmanager),
    key(key)
{
    queue = nullptr;
    base_center_x = image->get_center_x();
    base_center_y = image->get_center_y();
    base_scale_x = image->get_scale_x();
    base_scale_y = image->get_scale_y();
}

void ImageButton::set_on_click(std::function<void()> on_press_function)
{
    on_press_functions.push_back(on_press_function);
}

bool ImageButton::clicked_at(float x, float y)
{
    if (image->includes(x,y))
    {
        return is_clicked();
    }
    return false;
}

bool ImageButton::key_pressed(int key)
{
    if (this->key == key)
    {
        return is_clicked();
    }
    return false;
}

bool ImageButton::is_clicked()
{
    tmanager->remove_tween_queue(queue);
    return_to_basic_size();
    for (auto on_press_function : on_press_functions)
    {
        on_press_function();
    }
    add_tween_on_click();
    return true;
}

void ImageButton::add_tween_on_click()
{
    auto start_x = image->get_scale_x();
    auto start_y = image->get_scale_y();
    auto final_x = start_x / 2;
    auto final_y = start_y / 2;

    queue = std::make_shared<TweenQueue>();   
    queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, 0.1, sin_in_out));
    queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, start_x, start_y, 0.1, sin_in_out));
    tmanager->add_tween_queue(queue);

}

void ImageButton::paint()
{
    image->paint();
}

void ImageButton::return_to_basic_size()
{
    image->set_scale(base_scale_x, base_scale_y);
    image->set_center(base_center_x, base_center_y);
}
