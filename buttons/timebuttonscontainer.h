#ifndef TIMEBUTTONSCONTAINER_H
#define TIMEBUTTONSCONTAINER_H
#include "source/image.h"
#include "source/buttons/imagebutton.h"
#include "source/buttons/doubleimagebutton.h"
#include "source/resourceloader.h"

#include <vector>

class TimeButtonsContainer
{
    public:
        TimeButtonsContainer(float center_x, float center_y, float scale_x, float scale_y,
                             ResourceLoaderPtr resource_loader, SceneInfoPtr scene_info, TweenManagerPtr tmanager);
        bool clicked_at(float x, float y);
        void paint();
        bool key_pressed(int key);
        float get_haste_modifier();
    private:
        const int NUM_OF_BUTTONS = 3;
        float haste_modifier;
        ImageButtonPtr delay_button;
        ImageButtonPtr haste_button;
        DoubleImageButtonPtr pause_button;
        std::vector <ImageButtonPtr> buttons;
        bool pause_flag;
        void pause_reels();
        void delay_reels();
        void haste_reels();

};

typedef std::shared_ptr <TimeButtonsContainer> TimeButtonsContainerPtr;

#endif // TIMEBUTTONSCONTAINER_H
