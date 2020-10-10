#ifndef GLDRAWING_H
#define GLDRAWING_H
#include "source/sceneinfo.h"
#include "source/textureinfo.h"
#include "source/shader.h"
#include <vector>
#include <memory>

#define GLEW_STATIC

class GlObject
{
    public:
        GlObject() = delete;
        GlObject(TextureInfoPtr texture_info, SceneInfoPtr scene_info);
        GlObject(float center_x, float center_y, float scale_x, float scale_y,
                  TextureInfoPtr texture_info, SceneInfoPtr scene_info);

        TextureInfoPtr texture_info;
        SceneInfoPtr scene_info;

        void paint();
        void set_scale(float x, float y);
        void set_scale_x(float x);
        void set_scale_y(float y);
        void set_center(float x, float y);
        void set_center_x(float x);
        void set_center_y(float y);
        float get_scale_x();
        float get_scale_y();
        float get_center_x();
        float get_center_y();
        void move_y(float speed);

    protected :
        float left, right, top, bottom;

        void gl_to_pixel(float gl_x, float gl_y, float &pix_x, float &pix_y); //используется в наследнике
        void recount_coords();

    private:

        float scale_x, scale_y;
        float center_x, center_y;

        GLfloat vertices[32] =
        {
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
               -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
               -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
         };
        GLuint indices[6] = {
            0, 1, 3,
            1, 2, 3
        };
};

#endif // GLDRAWING_H
