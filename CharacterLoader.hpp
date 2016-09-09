#ifndef _CHARACTERLOADER_
#define _CHARACTERLOADER_

#include "IResourceLoader.hpp"
#include "POJO.hpp"
#include <string>
#include <list>
#include <sstream>

// Forward declaration
namespace tinyxml2
{
    class XMLNode;
}

class CharacterLoader: public IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data);

private:
    void parseControllers(CharacterPOJO* item, tinyxml2::XMLElement* l_data);
    void parseFrames(CharacterPOJO* item, tinyxml2::XMLElement* l_data);
};

#endif // _CHARACTERLOADER_
