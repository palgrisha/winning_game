#include "globject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

GlObject::GlObject(TextureInfoPtr texture_info, SceneInfoPtr scene_info) :
    texture_info(texture_info),
    scene_info(scene_info)
{
}

GlObject::GlObject(float center_x, float center_y, float scale_x, float scale_y,
          std::shared_ptr <TextureInfo> texture_info, std::shared_ptr <SceneInfo> scene_info) :
    texture_info(texture_info),
    scene_info(scene_info),
    scale_x(scale_x),
    scale_y(scale_y),
    center_x(center_x),
    center_y(center_y)
{
    recount_coords();
}

void GlObject::gl_to_pixel(float gl_x, float gl_y, float &pix_x, float &pix_y)
{
    pix_x = (gl_x+1)*scene_info->width/2;
    pix_y = (gl_y+1)*scene_info->height/2;
}

void GlObject::move_y(float speed)
{
    top -= speed / scene_info->height*2;
    bottom -= speed / scene_info->height*2;
    center_y -= speed;
}

void GlObject::recount_coords()
{
    left = (center_x - scale_x * texture_info->width / 2) / scene_info->width * 2 - 1;
    right = (center_x + scale_x * texture_info->width / 2) / scene_info->width * 2 - 1;
    top = (center_y + scale_y * texture_info->height / 2) / scene_info->height * 2 - 1;
    bottom = (center_y - scale_y * texture_info->height / 2) / scene_info->height * 2 - 1;
}

void GlObject::paint()
{
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    vertices[0] = vertices[8] = right;
    vertices[16] = vertices[24] = left;
    vertices[1] = vertices[25] = bottom;
    vertices[9] = vertices[17] = top;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, texture_info->index);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

float GlObject::get_center_x()
{
    return center_x;
}

float GlObject::get_center_y()
{
    return center_y;
}

float GlObject::get_scale_x()
{
    return scale_x;
}

float GlObject::get_scale_y()
{
    return scale_y;
}

void GlObject::set_center(float x, float y)
{
    center_x = x;
    center_y = y;
    recount_coords();
}

void GlObject::set_center_x(float x)
{
    center_x = x;
    recount_coords();
}

void GlObject::set_center_y(float y)
{
    center_y = y;
    recount_coords();
}

void GlObject::set_scale(float x, float y)
{
    scale_x = x;
    scale_y = y;
    recount_coords();
}

void GlObject::set_scale_x(float x)
{
    scale_x = x;
    recount_coords();
}

void GlObject::set_scale_y(float y)
{
    scale_y = y;
    recount_coords();
}
