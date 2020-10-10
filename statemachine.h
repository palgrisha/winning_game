#pragma once
#include <functional>
#include "rotationmanager.h"
#include "countingmanager.h"
#include "reel.h"
#include "resourceloader.h"
#include "drawingmanager.h"
#include "sceneinfo.h"
#include <vector>
#include "buttons/doublestatebutton.h"
#include "timermanager.h"

//add singletone

enum class State
{
    WAITING,
    ROTATING,
    COUNTING
};

class StateMachine
{
    public:
        StateMachine(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info);
        void update(float dt);
        void keyboard_pressed(int key);
        void clicked(float x, float y);
        const float MAX_TIME_FOR_ROTATION = 1;
    private:
        RotationManagerPtr rotation_manager;
        CountingManagerPtr counting_manager;
        State state;
        DoubleStateButtonPtr start_button;
        DoubleStateButtonPtr stop_button;
        std::vector <ImageButtonPtr> buttons;
        void start();
        void stop();
        TimerManagerPtr timer_manager;
        TimerPtr rotate_timer;
        TweenManagerPtr tween_manager;
};
