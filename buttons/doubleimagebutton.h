#ifndef DOUBLEIMAGEBUTTON_H
#define DOUBLEIMAGEBUTTON_H
#include "source/buttons/imagebutton.h"

enum class ImageType
{
    active, passive
};

class DoubleImageButton : public ImageButton
{
    public:
        DoubleImageButton(ImagePtr image, TweenManagerPtr tmanager, int key, ImagePtr passive_image);

        virtual void change_active_image(ImageType type);

    protected:
        ImagePtr passive_image;
        ImageType current_type;
        void reset_active();

};

typedef std::shared_ptr <DoubleImageButton> DoubleImageButtonPtr;

#endif // DOUBLEIMAGEBUTTON_H
