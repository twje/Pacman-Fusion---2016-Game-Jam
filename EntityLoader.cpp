#include "tinyxml2.h"
#include "EntityLoader.hpp"
#include <string>
#include <stdexcept>

Object* EntityLoader::loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data)
{
    EntityPOJO* item = new EntityPOJO();
    try {
        item->m_id = l_id;
        item->m_texture = getString(l_data->FirstChildElement("texture"));
        item->m_width = getInt(l_data->FirstChildElement("width"));
        item->m_height = getInt(l_data->FirstChildElement("height"));
        item->m_startFrame = getInt(l_data->FirstChildElement("startFrame"));
        item->m_tileX = getInt(l_data->FirstChildElement("tileX"));
        item->m_tileY = getInt(l_data->FirstChildElement("tileY"));
        item->m_layer = getInt(l_data->FirstChildElement("layer"));
    } catch(std::exception& e) {
        throw std::runtime_error("runtime_error - " + std::string(e.what()));
    }
    return item;
}
