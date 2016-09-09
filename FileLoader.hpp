#ifndef _FILELOADER_
#define _FILELOADER_

#include <SFML/Graphics.hpp>
#include "IResourceLoader.hpp"
#include "Common.hpp"

// Forward declaration
namespace tinyxml2
{
    class XMLNode;
}

//**************
// TextureLoader
//**************
class FileLoader: public IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data);
};

#endif // _FILELOADER_
