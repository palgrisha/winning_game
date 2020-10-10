#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <map>
#include <memory>
#include "source/textureinfo.h"

class ResourceLoader
{
    public:
        ResourceLoader(){}
        void put(std::string key, std::string path);
        TextureInfoPtr get(std::string key);
    private :
        std::map <std::string, TextureInfo> textures;
};

typedef std::shared_ptr <ResourceLoader> ResourceLoaderPtr;

#endif // RESOURCELOADER_H
