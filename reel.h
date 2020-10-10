#ifndef REEL_H
#define REEL_H
//#include "image.h"
#include "resourceloader.h"
#include <memory>
#include <vector>
#include "tweens/tweenmanager.h"
#include "tweens/tweencurves.h"
#include "drawingmanager.h"
#include "doubleimage.h"



class Reel
{
    public:
        constexpr static int FIGURES_IN_REEL = 3;
        constexpr static float TIME_FOR_SPEED_INCREASE = 0.2;
        constexpr static float AVERAGE_SPEED = 4.0;


        Reel(float left, float right, float top, float bottom,
            ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info, TweenManagerPtr tmanager, DrawingManagerPtr drawing_manager);


        void paint();
        float get_distance();
        bool stopped();
        void update(float dt);

        enum class State
        {
            IDLE,
            HASTE,
            UNIFORM,
            DELAY,
            RETURNING
        };

        void haste();
        void stop();
        std::vector <DoubleImagePtr> get_final_set();

    private:
        float left, right, top, bottom;
        std::vector <DoubleImagePtr> images;
        float current_speed;
        float final_speed;
        float boost;
        float stop_timer;
        TweenQueuePtr queue_canary;

        ResourceLoaderPtr resource_loader;
        SceneInfoPtr scene_info;
        TweenManagerPtr tmanager;
        DrawingManagerPtr drawing_manager;
      //  TextureInfoPtr get_random_figure_index();
        DoubleImagePtr get_random_figure();

        State state;
        void correct_images_positions();
        void shift_images();
        int rand(int max);
};

typedef std::shared_ptr <Reel> ReelPtr;

#endif // REEL_H
