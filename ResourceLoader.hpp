#ifndef _RESOURCELOADER_
#define _RESOURCELOADER_

#include <string>
#include <map>
#include <list>
#include "ResourceLoader.hpp"

// Forward declaration
class IResourceLoader;
class Object;
namespace tinyxml2
{
    class XMLDocument;
    class XMLNode;
}

namespace ResourceType
{
    extern const std::string TEXTURE;
    extern const std::string FONT;
    extern const std::string ENTITY;
    extern const std::string CHARACTER;
    extern const std::string FILE;
}

using ResourceEntry = std::pair<std::string, tinyxml2::XMLNode*>;
using ResourceCache = std::map<std::string, ResourceEntry>;
using ResourceAtlas = std::map<std::string, ResourceCache>;

//*********************
// ResourceManagerState
//*********************
class ResourceLoader {
private:
    std::map<std::string, IResourceLoader*> m_loaders;
    std::list<tinyxml2::XMLDocument*> m_docs;
    ResourceAtlas m_store;

public:
    ResourceLoader(std::string l_path);
    ~ResourceLoader();

    Object* loadResource(std::string l_type, std::string l_id);

private:
    void loadFromManifest(std::string l_path);
    void parseResources(tinyxml2::XMLNode *node);
    bool isResourceLoaderSet(std::string l_type);
    tinyxml2::XMLDocument* loadDOM(std::string l_path);
    std::string getBaseResourcePath(tinyxml2::XMLNode* l_resourceNode);
    void purge();
};

#endif // _RESOURCELOADER_
