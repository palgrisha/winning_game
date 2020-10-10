#include "resourceloader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

void ResourceLoader::put(std::string key, std::string path)
{
    GLuint res;
    glGenTextures(1, &res);
    glBindTexture(GL_TEXTURE_2D, res);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int tex_width, tex_height;   
    unsigned char* image = SOIL_load_image(path.c_str(), &tex_width, &tex_height, 0, SOIL_LOAD_RGB);
    textures.insert({key, TextureInfo(res, tex_width, tex_height)});
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr <TextureInfo> ResourceLoader::get(std::string key)
{
    return std::make_shared<TextureInfo>(textures.find(key)->second);
}
