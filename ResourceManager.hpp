#ifndef _RESOURCEMANAGER_
#define _RESOURCEMANAGER_

#include <memory>
#include "ResourceLoader.hpp"
#include "Common.hpp"
#include "Utilities.h"

//****************
// ResourceManager
//****************
class ResourceManager
{
private:
    static ResourceManager* m_self;

    std::map<std::string, std::map<std::string, std::pair<Object*, unsigned int>>> m_resources;
    ResourceLoader m_loader;

    ResourceManager(std::string l_path):
    m_loader(l_path)
    {}

public:
    ~ResourceManager() { /* implement purge */ }

    static ResourceManager* getInstance(){

        if (!m_self) { m_self = new ResourceManager(Utils::GetWorkingDirectory() + "manifest.xml"); }

        return m_self;
    }

    bool requireResource(std::string l_type, std::string l_id) {
        // resource exists
        std::cout << "Enter" << std::endl;

        auto resourcePair = findResource(l_type, l_id);
        std::cout << "a" << std::endl;
        if (resourcePair) {
            ++resourcePair->second;
            return true;

            std::cout << "b" << std::endl;
        }

        // load resource
        Object* resource = nullptr;
        try {
            std::cout << "c" << std::endl;
            resource = m_loader.loadResource(l_type, l_id);
            std::cout << "d" << std::endl;
        } catch (std::exception& e) {

            std::cout << "This did work" << std::endl;

            return false;
        }

        m_resources[l_type].emplace(l_id, std::make_pair(resource, 1));
        std::cout << "e" << std::endl;
        return true;
    }

    bool releaseResource(std::string l_type, std::string l_id) {
        auto resource = findResource(l_type, l_id);
        if (!resource){ return false; }
        --resource->second;
        if (!resource->second){ return unload(l_type, l_id); }
        return true;
    }

    template<typename T>
    T* getResource(std::string l_type, std::string l_id) {
        if (!isResourceAvailable(l_type, l_id)){ return nullptr; }

        Object* object = m_resources[l_type][l_id].first;
        T* result =( T*)object->getSelf();

        return result;
    }

    template<typename T>
    std::unique_ptr<T> newResource(std::string l_type, std::string l_id) {
        std::unique_ptr<T> result(nullptr);

        // load resource
        Object* object = nullptr;
        try {
            object = m_loader.loadResource(l_type, l_id);
        } catch (std::exception& e) {
            return result;
        }
        result.reset((T*)object->getSelf());

        // Resource does not inherit from Object (safely delete)
        if ((void*)object != (void*)object->getSelf()) { delete object; }

        return std::move(result);
    }

private:
    std::pair<Object*, unsigned int>* findResource(std::string l_type, std::string l_id) {
        if (!isResourceAvailable(l_type, l_id)){ return nullptr; }

        return &m_resources[l_type][l_id];
	}

    bool unload(std::string l_type, std::string l_id) {
        if (!isResourceAvailable(l_type, l_id)){ return false; }

        Object* object = m_resources[l_type][l_id].first;

        // Resource does not inherit from Object (delete both)
        if ((void*)object != (void*)object->getSelf()) {
            delete object->getSelf();
        }
        delete object;

        m_resources[l_type].erase(l_id);
		return true;
	}

	bool isResourceAvailable(std::string l_type, std::string l_id) {
        if (m_resources.find(l_type) == m_resources.end()){ return false; }
        if ((m_resources[l_type]).find(l_id) == (m_resources[l_type]).end()){ return false; }

        return true;
	}
};

#endif // _RESOURCEMANAGER_
