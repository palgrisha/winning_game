#ifndef DRAWINGMANAGER_H
#define DRAWINGMANAGER_H
#include <vector>
#include "image.h"
#include <memory>

class DrawingManager
{
public:
    DrawingManager() = default;
    void draw();
    void add(ImagePtr image, int back_offset = 2);
    void remove(ImagePtr image);
private:
    std::vector <ImagePtr> images;

};

typedef std::shared_ptr <DrawingManager> DrawingManagerPtr;
#endif // DRAWINGMANAGER_H
