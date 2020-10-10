#include "drawingmanager.h"
#include "image.h"

void DrawingManager::draw()
{
    for (auto image : images)
    {
        if (image->is_visible())
        {
            image->draw();
        }
    }
}

void DrawingManager::add(ImagePtr image, int back_offset)
{
    images.insert(images.end() - back_offset, image);
}

void DrawingManager::remove(ImagePtr image)
{
    for (auto it = images.begin(); it < images.end();)
    {
        if (*it == image)
        {
            images.erase(it);
        }

        else
        {
            it++;
        }
    }
}
