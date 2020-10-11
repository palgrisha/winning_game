#ifndef ROTATIONMANAGER_H
#define ROTATIONMANAGER_H
#include <memory>
#include "drawingmanager.h"
#include "reel.h"
#include "resourceloader.h"
#include "sceneinfo.h"
#include "timermanager.h"
#include <vector>

class RotationManager
{
public:
    RotationManager(DrawingManagerPtr drawing_manager, ResourceLoaderPtr resource_loader,
                    SceneInfoPtr scene_info, TimerManagerPtr timer_manager, TweenManagerPtr tween_manager);
    void update(float dt);
    void stop_reels();
    void start_reels();
    bool stopped();
    std::vector <std::vector <DoubleImagePtr>> get_final_set();
    const static int REELS_AT_TABLE = 5;
    constexpr static float MAX_TIME_FOR_ROTATION = 1;
    constexpr static float TIMER_MODIFICATOR = 0.5;
    constexpr static float FRAME_SIZE = 0.1;
private:
    std::vector <ReelPtr> reels;
    DrawingManagerPtr drawing_manager;
    ResourceLoaderPtr resource_loader;
    SceneInfoPtr scene_info;
    TimerManagerPtr timer_manager;
    TweenManagerPtr tween_manager;
};

typedef std::shared_ptr <RotationManager> RotationManagerPtr;

#endif // ROTATIONMANAGER_H
