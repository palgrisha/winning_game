#ifndef DOUBLEIMAGE_H
#define DOUBLEIMAGE_H
#include "image.h"

class DoubleImage : public Image
{
public:
    DoubleImage(TextureInfoPtr texture_info, SceneInfoPtr scene_info, TextureInfoPtr passive_info);
    DoubleImage(float center_x, float center_y, float scale_x, float scale_y,
          TextureInfoPtr texture_info, SceneInfoPtr scene_info, TextureInfoPtr passive_info);
    void swap_textures();
private:
    TextureInfoPtr passive_info;
};

typedef std::shared_ptr <DoubleImage> DoubleImagePtr;
#endif // DOUBLEIMAGE_H
