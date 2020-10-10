#include "doubleimage.h"

DoubleImage::DoubleImage(TextureInfoPtr texture_info, SceneInfoPtr scene_info, TextureInfoPtr passive_info):
    Image(texture_info, scene_info),
    passive_info(passive_info)
{
}

DoubleImage::DoubleImage(float center_x, float center_y, float scale_x, float scale_y,
      TextureInfoPtr texture_info, SceneInfoPtr scene_info, TextureInfoPtr passive_info):

    Image(center_x, center_y, scale_x, scale_y, texture_info, scene_info),
    passive_info(passive_info)
{
}

void DoubleImage::swap_textures()
{
    auto temp = passive_info;
    passive_info = texture_info;
    texture_info = temp;
}
