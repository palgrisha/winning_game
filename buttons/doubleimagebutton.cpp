#include "doubleimagebutton.h"

DoubleImageButton::DoubleImageButton(ImagePtr image, TweenManagerPtr tmanager, int key, ImagePtr passive_image) :
    ImageButton(image, tmanager, key),
    passive_image(passive_image)
{
    passive_image->set_center(image->get_center_x(), image->get_center_y());
    passive_image->set_scale(image->get_center_x(), image->get_center_y());
    passive_image->set_visible(false);
    current_type = ImageType::active;
}

void DoubleImageButton::change_active_image(ImageType type)
{
    if (current_type == type)
    {
        return;
    }

    return_to_basic_size();

    auto temp = image;
    image = passive_image;
    passive_image = temp;

    passive_image->set_visible(false);
    image->set_visible(true);

    return_to_basic_size();

    current_type = type;
}

