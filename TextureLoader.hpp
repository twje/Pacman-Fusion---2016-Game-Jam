#ifndef _TEXTURELOADER_
#define _TEXTURELOADER_

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
class TextureLoader: public IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data);
};

#endif // _TEXTURELOADER_
