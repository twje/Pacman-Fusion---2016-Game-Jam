#ifndef _ENTITYLOADER_
#define _ENTITYLOADER_

#include "IResourceLoader.hpp"
#include "POJO.hpp"
#include <string>


// Forward declaration
namespace tinyxml2
{
    class XMLNode;
}

class EntityLoader: public IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data);
};


#endif // _ENTITYLOADER_
