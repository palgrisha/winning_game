#include "doublestatebutton.h"

DoubleStateButton::DoubleStateButton(ImagePtr image, TweenManagerPtr tmanager, int key, ImagePtr passive_image) :
    DoubleImageButton(image, tmanager, key, passive_image)
{
    add_cycled_tween();
}

bool DoubleStateButton::is_clicked()
{
    if (current_type == ImageType::passive)
    {
        return false;
    }
    return ImageButton::is_clicked();
}

void DoubleStateButton::add_cycled_tween()
{   
    auto start_x = image->get_scale_x();
    auto start_y = image->get_scale_y();
    auto final_x = start_x * 3 / 4;
    auto final_y = start_y * 3 / 4;

    queue = std::make_shared<CycledQueue>();
    queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, 0.5, linear));
    queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, start_x, start_y, 0.5, sin_in_out));
    tmanager->add_tween_queue(queue);
}

void DoubleStateButton::change_active_image(ImageType type)
{
    DoubleImageButton::change_active_image(type);
    if (type == ImageType::active)
    {
        add_cycled_tween();
    }
}
