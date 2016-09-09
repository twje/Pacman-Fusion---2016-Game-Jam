#include "tinyxml2.h"
#include "ResourceLoader.hpp"
#include "Utilities.h"
#include <iostream>
#include <stack>
#include <sstream>

#include "TextureLoader.hpp"
#include "EntityLoader.hpp"
#include "FontLoader.hpp"
#include "CharacterLoader.hpp"
#include "FileLoader.hpp"

namespace ResourceType
{
    const std::string TEXTURE = "texture";
    const std::string FONT = "font";
    const std::string ENTITY = "entity";
    const std::string CHARACTER = "character";
    const std::string FILE = "file";
}

ResourceLoader::ResourceLoader(std::string l_path) {

    // init loaders
    m_loaders[ResourceType::TEXTURE] = new TextureLoader();
    m_loaders[ResourceType::FONT] = new FontLoader();
    m_loaders[ResourceType::ENTITY] = new EntityLoader();
    m_loaders[ResourceType::CHARACTER] = new CharacterLoader();
    m_loaders[ResourceType::FILE] = new FileLoader();

    loadFromManifest(l_path);
}

ResourceLoader::~ResourceLoader(){ purge(); }

Object* ResourceLoader::loadResource(std::string l_type, std::string l_id) {

    if (m_store.find(l_type) == m_store.end()){ throw std::logic_error("logic_error - request for not existant resource type: " + l_type); }
    ResourceCache& cache = m_store[l_type];

    if (cache.find(l_id) == cache.end()){
        std::stringstream ss;
        ss << "logic_error - resource id " << l_id << " of type " << l_type << " is not present in manifest.xml";
        std::cout << ss.str() << std::endl;
        throw std::logic_error(ss.str());
    }

    std::string l_basePath = (m_store[l_type][l_id]).first;
    tinyxml2::XMLNode* l_data = (m_store[l_type][l_id]).second;

    IResourceLoader* loader = m_loaders[l_type];
    Object* result = loader->loadResource(l_id, Utils::GetWorkingDirectory() + l_basePath, l_data);

    return result;
}

void ResourceLoader::loadFromManifest(std::string l_path) {
    std::stack<tinyxml2::XMLDocument*> l_queue;
    l_queue.push(loadDOM(l_path));

    while(!l_queue.empty()) {
        tinyxml2::XMLNode* node = l_queue.top()->FirstChildElement("manifest")->FirstChild();
        l_queue.pop();

        while( node )
        {
            if (strcmp( node->Value(), "resource" ) == 0)
            {
                parseResources(node);
            }

            if (strcmp( node->Value(), "link" ) == 0)
            {
                std::string path = Utils::GetWorkingDirectory() + std::string(node->ToElement()->GetText());
                l_queue.push(loadDOM(path));
            }
            node = node->NextSibling();
        }
    }
}

void ResourceLoader::parseResources(tinyxml2::XMLNode *node)
{
    // pre-init
    std::string l_type = node->FirstChildElement("type")->GetText();
    std::string l_path = getBaseResourcePath(node);

    if (!isResourceLoaderSet(l_type)) {
        throw std::logic_error("logic_error - resource loader not supported: " + l_type);
    }
    if (m_store.find(l_type) == m_store.end()) { m_store.emplace(l_type, ResourceCache()); }

    // parse
    tinyxml2::XMLNode *itemNode = node->FirstChildElement("item");
    while(itemNode)
    {
        std::string id = itemNode->FirstChildElement("id")->GetText();

        auto entry = std::make_pair(l_path, itemNode->FirstChildElement("data"));

        auto result = m_store[l_type].emplace(id, entry);
        if (!result.second){ throw std::runtime_error("runtime_error - duplicate resources in manifest.xml: " + l_type); }


        itemNode = itemNode->NextSiblingElement("item");
    }
}

bool ResourceLoader::isResourceLoaderSet(std::string l_type) {
    return m_loaders.find(l_type) != m_loaders.end();
}

tinyxml2::XMLDocument* ResourceLoader::loadDOM(std::string l_path) {
    auto result = new tinyxml2::XMLDocument();

    result->LoadFile( l_path.c_str() );
    if (result->Error()) {
        throw std::runtime_error("runtime_error - unable to parse manifest.xml: " + l_path);
    }
    m_docs.push_back(result);

    return result;
}

std::string ResourceLoader::getBaseResourcePath(tinyxml2::XMLNode* l_resourceNode) {

    auto baseNode = l_resourceNode->FirstChildElement("base");

    return (baseNode ? baseNode->GetText() : ""); // return default value if xme tage is not present
}

void ResourceLoader::purge() {
    for(auto loader : m_loaders) { delete loader.second; }
    for(auto doc : m_docs){ delete doc; }

    m_loaders.clear();
    m_docs.clear();
    m_store.clear();
}
