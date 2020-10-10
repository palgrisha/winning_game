#include "timebuttonscontainer.h"

TimeButtonsContainer::TimeButtonsContainer(float center_x, float center_y, float scale_x, float scale_y,
                                   ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info, TweenManagerPtr tmanager)
{
    haste_modifier = 1;
    pause_flag = false;

    auto haste_info = resource_loader->get("haste");
    auto haste_image = std::make_shared<Image>(resource_loader->get("haste"), scene_info);
    haste_image->set_center(center_x + 20 + haste_info->width*scale_x, center_y);
    haste_image->set_scale(scale_x, scale_y);
    haste_button = std::make_shared <ImageButton>(haste_image, tmanager, GLFW_KEY_A);
    haste_button->set_on_click([this](){haste_reels();});
    buttons.push_back(haste_button);

    auto pause_image = std::make_shared<Image>(resource_loader->get("pause"), scene_info);
    auto continue_image = std::make_shared<Image>(resource_loader->get("circle"), scene_info);
    pause_image->set_center(center_x, center_y);
    pause_image->set_scale(scale_x, scale_y);
    pause_button = std::make_shared <DoubleImageButton> (pause_image, tmanager, GLFW_KEY_P, continue_image);
    pause_button->set_on_click([this](){pause_reels();});
    buttons.push_back(pause_button);

    auto delay_info = resource_loader->get("delay");
    auto delay_image = std::make_shared<Image>(delay_info, scene_info);
    delay_image->set_center(center_x - 20 - delay_info->width*scale_x, center_y);
    delay_image->set_scale(scale_x, scale_y);
    delay_button = std::make_shared <ImageButton> (delay_image, tmanager, GLFW_KEY_D);
    delay_button->set_on_click([this](){delay_reels();});
    buttons.push_back(delay_button);
}

void TimeButtonsContainer::paint()
{
    for (auto button : buttons)
    {
        button->paint();
    }
}

bool TimeButtonsContainer::clicked_at(float x, float y)
{
    for (auto button : buttons)
    {
        if (button->clicked_at(x,y))
        {
            return true;
        }
    }
    return false;
}

bool TimeButtonsContainer::key_pressed(int key)
{
    for (auto button : buttons)
    {
        if (button->key_pressed(key))
        {
            return true;
        }
    }
    return false;
}

float TimeButtonsContainer::get_haste_modifier()
{
    if (pause_flag)
    {
        return 0;
    }
    return haste_modifier;
}

void TimeButtonsContainer::pause_reels()
{
    pause_flag = !pause_flag;
    if (pause_flag)
    {
        pause_button->change_active_image(ImageType::passive);
    }
    else
    {
        pause_button->change_active_image(ImageType::active);
    }
}

void TimeButtonsContainer::delay_reels()
{
    if (haste_modifier <= 1.0 / 8)
    {
        return;
    }
    haste_modifier /= 2;
}

void TimeButtonsContainer::haste_reels()
{
    if (haste_modifier >= 8)
    {
        return;
    }
    haste_modifier *= 2;
}

