#ifndef TWEENCOORD_H
#define TWEENCOORD_H
#include "tweens/tweenbase.h"

class TweenCoord : public TweenBase
{
    public:
        TweenCoord(ImagePtr figure, float final_center_x, float final_center_y,
                   float time, std::function <float(float)> tween_curve);
        TweenCoord(ImagePtr image, float start_coord_x, float start_coord_y, float final_coord_x, float final_coord_y,
                   float time, std::function <float(float)> tween_curve);
        void update(float dt) override;

    private :
        float final_center_x, final_center_y;
        float start_center_x, start_center_y;
};

typedef std::shared_ptr <TweenCoord> TweenCoordPtr;
#endif // TWEENCOORD_H
