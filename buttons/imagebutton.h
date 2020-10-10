#ifndef BUTTON_H
#define BUTTON_H
#include "image.h"
#include "tweens/tweenmanager.h"
#include <functional>
#include <memory>
#include "tweens/tweencurves.h"
#include <vector>

class ImageButton
{
    public:
        ImageButton(ImagePtr image, TweenManagerPtr tmanager, int key);
        bool clicked_at(float x, float y);
        bool key_pressed(int key);
        void paint();
        void set_on_click(std::function<void(void)> click_function);
    protected:
        virtual bool is_clicked();
        ImagePtr image;        
        TweenQueuePtr queue;
        TweenManagerPtr tmanager;
        void return_to_basic_size();
    private:        
        float base_center_x, base_center_y;
        float base_scale_x, base_scale_y;
        void add_tween_on_click();
        std::vector <std::function<void()>> on_press_functions;
        int key;
};

typedef std::shared_ptr <ImageButton> ImageButtonPtr;

#endif // BUTTON_H
