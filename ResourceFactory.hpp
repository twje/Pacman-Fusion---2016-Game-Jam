#ifndef _RESOURCEFACTORY_
#define _RESOURCEFACTORY_

#include "POJO.hpp"

//****************
// ResourceFactory
//****************
class ResourceFactory
{
public:
    static CharacterPOJO* getCharatcerPojo(std::string id) {
        auto manager = ResourceManager::getInstance();
        auto ptn = manager->newResource<CharacterPOJO>(ResourceType::CHARACTER, id);

        if (ptn.get() == nullptr){ throw std::logic_error("logic_error - resource should exist"); }

        return ptn.release();
    }

    static EntityPOJO* getEntityPojo(std::string id) {
        auto manager = ResourceManager::getInstance();
        auto ptn = manager->newResource<EntityPOJO>(ResourceType::ENTITY, id);

        if (ptn.get() == nullptr){ throw std::logic_error("logic_error - resource should exist"); }

        return ptn.release();
    }
};

#endif // _RESOURCEFACTORY_
