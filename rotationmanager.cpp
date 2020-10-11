#include "rotationmanager.h"


RotationManager::RotationManager(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info,
                                 TimerManagerPtr timer_manager, TweenManagerPtr tween_manager):
    drawing_manager(drawing_manager),
    resource_loader(resource_loader),
    scene_info(scene_info),
    timer_manager(timer_manager),
    tween_manager(tween_manager)
{
    auto frame_width = scene_info->width * FRAME_SIZE;
    auto frame_height = scene_info->height * FRAME_SIZE;
    auto desk_width = scene_info->width - 2 * frame_width;
    auto desk_height = scene_info->height - 2 * frame_height;

    for (int i = 0; i < REELS_AT_TABLE; i++)
    {
        auto current_left = frame_width + (desk_width - 2 * frame_width) * i / REELS_AT_TABLE;
        auto current_right = (desk_width - 2*frame_width) * (i+1) / REELS_AT_TABLE + frame_width;
        reels.push_back(std::make_shared<Reel>
                           (current_left,
                            current_right,
                            desk_height+frame_height,
                            frame_height,
                            resource_loader,
                            scene_info,
                            tween_manager,
                            drawing_manager));
    }
}

void RotationManager::update(float dt)
{
    for (auto reel : reels)
    {
        reel->update(dt);
    }
}

void RotationManager::start_reels()
{
    for (auto reel : reels)
    {
        reel->haste();
    }
}

void RotationManager::stop_reels()
{
    reels.at(0)->stop();
    for (size_t i = 1; i < reels.size(); i++)
    {
        auto timer = std::make_shared<Timer>(i*TIMER_MODIFICATOR, [this, i](){reels.at(i)->stop();});
        timer_manager->add_timer(timer);
    }
}

bool RotationManager::stopped()
{
    for (auto reel : reels)
    {
        if (!reel->stopped())
        {
            return false;
        }
    }
    return true;
}

std::vector <std::vector <DoubleImagePtr>> RotationManager::get_final_set()
{
    std::vector <std::vector <DoubleImagePtr>> set;

    for (auto reel : reels)
    {
        set.push_back(reel->get_final_set());
    }

    return set;
}
