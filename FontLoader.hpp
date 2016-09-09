#ifndef _FONTLOADER_
#define _FONTLOADER_

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
class FontLoader: public IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data);
};

#endif // _FONTLOADER_
