#ifndef _IRESOURCELOADER_
#define _IRESOURCELOADER_

#include "tinyxml2.h"
#include <stdexcept>
#include <string>

// Forward declaration
class Object;

//****************
// IResourceLoader
//****************
class IResourceLoader {
public:
    virtual Object* loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data) = 0;

    int getInt(tinyxml2::XMLNode* l_node) {
        if (!l_node) { throw std::logic_error("logic_error - value can not be parsed"); }

        return std::stoi(l_node->ToElement()->GetText());
    }

    std::string getString(tinyxml2::XMLNode* l_node) {
        if (!l_node) { throw std::logic_error("logic_error - value can not be parsed"); }

        return l_node->ToElement()->GetText();
    }
};

#endif // _IRESOURCELOADER_
