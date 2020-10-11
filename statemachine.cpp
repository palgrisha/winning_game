#include "statemachine.h"
#include "makestartobjects.h"

StateMachine::StateMachine(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info):
    drawing_manager(drawing_manager),
    resource_loader(resource_loader),
    scene_info(scene_info)
{


    timer_manager = std::make_shared <TimerManager>();
    tween_manager = std::make_shared <TweenManager>();

    state = State::WAITING;
    make_start_graphic_objects();

    rotation_manager = std::make_shared <RotationManager>(drawing_manager,
                                                          resource_loader,
                                                          scene_info,
                                                          timer_manager,
                                                          tween_manager);
    counting_manager = std::make_shared <CountingManager>(resource_loader);
}

void StateMachine::update(float dt)
{
    switch (state)
    {
        case State::ROTATING:
        {
            rotation_manager->update(dt);
            if (rotation_manager->stopped())
            {
                state = State::COUNTING;
                counting_manager->set_input(rotation_manager->get_final_set());
            }
            break;
        }

        case State::COUNTING:
        {
            counting_manager->update(dt);
            if (counting_manager->finished())
            {
                state = State::WAITING;
                start_button->change_active_image(ImageType::active);
            }
            break;
        }

        case State::WAITING:
        {
            break;
        }

    }

    timer_manager->update(dt);
    timer_manager->remove_empty_timers();

    tween_manager->update(dt);
    tween_manager->remove_empty_queues();
}

void StateMachine::clicked(float x, float y)
{
    for (auto button : buttons)
    {
        button->clicked_at(x,y);
    }
}

void StateMachine::keyboard_pressed(int key)
{
    for (auto button : buttons)
    {
        button->key_pressed(key);
    }
}

void StateMachine::start()
{
    if (state != State::WAITING)
    {
        return;
    }

    counting_manager->clear_marks();
    state = State::ROTATING;
    start_button->change_active_image(ImageType::passive);
    stop_button->change_active_image(ImageType::active);

    rotation_manager->start_reels();
    rotate_timer = std::make_shared<Timer>(MAX_TIME_FOR_ROTATION + Reel::TIME_FOR_SPEED_INCREASE, [this](){stop();});
    timer_manager->add_timer(rotate_timer);
}

void StateMachine::stop()
{
    if (state != State::ROTATING)
    {
        return;
    }

    timer_manager->remove_timer(rotate_timer);

    stop_button->change_active_image(ImageType::passive);

    rotation_manager->stop_reels();
}

void StateMachine::make_start_graphic_objects()
{
    const float FRAME_SIZE = 0.1;

    auto frame_height = scene_info->height * FRAME_SIZE;
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

    auto start_image_active = std::make_shared<Image>(resource_loader->get("start_active"), scene_info);
    auto start_image_passive = std::make_shared<Image>(resource_loader->get("start_passive"), scene_info);
    start_image_active->set_center(1500, 550);
    start_image_active->set_scale(0.3, 0.3);
    start_button = std::make_shared <DoubleStateButton>
            (start_image_active,
             tween_manager,
             GLFW_KEY_W,
             start_image_passive);
    start_button->set_on_click([this](){start();});
    buttons.push_back(start_button);

    //napisat functsiu avtodobavleniya obeih kartinok knopki
    drawing_manager->add(start_image_active);
    drawing_manager->add(start_image_passive);

    auto stop_image_active = std::make_shared<Image>(resource_loader->get("stop_active"), scene_info);
    auto stop_image_passive = std::make_shared<Image>(resource_loader->get("stop_passive"), scene_info);
    stop_image_active->set_center(1500, 350);
    stop_image_active->set_scale(0.3, 0.3);
    stop_button = std::make_shared <DoubleStateButton>
            (stop_image_active,
             tween_manager,
             GLFW_KEY_S,
             stop_image_passive);
    stop_button->set_on_click([this](){stop();});
    stop_button->change_active_image(ImageType::passive);
    buttons.push_back(stop_button);
    drawing_manager->add(stop_image_active);
    drawing_manager->add(stop_image_passive);
}
