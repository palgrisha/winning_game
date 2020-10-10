#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

class TextureInfo
{
    public:
        TextureInfo(GLuint index, int width, int height);
        int index;
        int width;
        int height;
};

typedef std::shared_ptr <TextureInfo> TextureInfoPtr;

#endif // TEXTUREINFO_H
