#ifndef DOUBLESTATEBUTTON_H
#define DOUBLESTATEBUTTON_H

#include "buttons/doubleimagebutton.h"
#include "tweens/tweenscale.h"

class DoubleStateButton : public DoubleImageButton
{
    public:
        DoubleStateButton(ImagePtr image, TweenManagerPtr tmanager, int key, ImagePtr passive_image);

        void change_active_image(ImageType type);

    protected:
        bool is_clicked();
        CycledQueuePtr queue;

    private:
        void add_cycled_tween();

};

typedef std::shared_ptr <DoubleStateButton> DoubleStateButtonPtr;

#endif // DOUBLESTATEBUTTON_H
