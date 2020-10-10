#include "makestartobjects.h"

void make_start_objects(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info,
                        DoubleStateButtonPtr start_button, DoubleStateButtonPtr stop_button)
{
    const float FRAME_SIZE = 0.1;

    auto frame_width = scene_info->width * FRAME_SIZE;
    auto frame_height = scene_info->height * FRAME_SIZE;
    auto desk_width = scene_info->width - 2 * frame_width;
    auto desk_height = scene_info->height - 2 * frame_height;

    float back_scale_x = scene_info->width / resource_loader->get("background")->width;
    float back_size_y = resource_loader->get("background")->height;

    auto center_curtain = std::make_shared<Image>(resource_loader->get("background"), scene_info);
    center_curtain->set_center(scene_info->width / 2, scene_info->height / 2);
    center_curtain->set_scale(back_scale_x, desk_height/back_size_y);
    drawing_manager->add(center_curtain, 0);

    auto up_curtain = std::make_shared<Image>(resource_loader->get("background"), scene_info);
    up_curtain->set_center(scene_info->width / 2, scene_info->height - frame_height / 2);
    up_curtain->set_scale(back_scale_x, frame_height / back_size_y);
    drawing_manager->add(up_curtain, 0);

    auto down_curtain = std::make_shared<Image>(resource_loader->get("background"), scene_info);
    down_curtain->set_center(scene_info->width / 2, frame_height / 2);
    down_curtain->set_scale(back_scale_x, frame_height / back_size_y);
    drawing_manager->add(down_curtain, 0);




}
