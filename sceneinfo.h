#ifndef SCENEINFO_H
#define SCENEINFO_H
#include <memory>

class SceneInfo
{   
    public:
        SceneInfo(int width, int height);
        int width;
        int height;
};

typedef std::shared_ptr <SceneInfo> SceneInfoPtr;

#endif // SCENEINFO_H
