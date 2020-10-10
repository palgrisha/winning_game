#ifndef FIGURES_H
#define FIGURES_H

#define GLEW_STATIC
#include <memory>
#include "source/globject.h"

class Image : public GlObject
{
    public:
        Image() = delete;
        Image(TextureInfoPtr texture_info, SceneInfoPtr scene_info);
        Image(float center_x, float center_y, float scale_x, float scale_y,
              TextureInfoPtr texture_info, SceneInfoPtr scene_info);

        bool includes(float x, float y);
        float get_top_pixel();
        float get_bottom_pixel();
};

typedef std::shared_ptr <Image> ImagePtr;

#endif // FIGURES_H
