#include "image.h"

Image::Image(std::shared_ptr<TextureInfo> texture_info, std::shared_ptr<SceneInfo> scene_info) :
    GlObject(texture_info, scene_info)
{}

Image::Image(float center_x, float center_y, float scale_x, float scale_y,
    std::shared_ptr<TextureInfo> texture_info, std::shared_ptr<SceneInfo> scene_info) :
    GlObject(center_x, center_y, scale_x, scale_y, texture_info, scene_info)
{}

bool Image::includes(float x, float y)
{
    if (left <= x && right >= x && top >= y && bottom <= y)
    {
        return true;
    }
    return false;
}

float Image::get_top_pixel()
{
    float pix_x, pix_y;
    gl_to_pixel(left, top, pix_x, pix_y);
    return pix_y;
}

float Image::get_bottom_pixel()
{
    float pix_x, pix_y;
    gl_to_pixel(left, bottom, pix_x, pix_y);
    return pix_y;
}
