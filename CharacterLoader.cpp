#include "tinyxml2.h"
#include "CharacterLoader.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

Object* CharacterLoader::loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data)
{
    CharacterPOJO* item = new CharacterPOJO();
    try {
        item->m_id = l_id;
        item->m_entity = getString(l_data->FirstChildElement("entity"));
        item->m_state = getString(l_data->FirstChildElement("state"));
        item->m_facing = getString(l_data->FirstChildElement("facing"));
        parseControllers(item, l_data->FirstChildElement("controllers"));
        parseFrames(item, l_data->FirstChildElement("anims"));
    } catch(std::exception& e) {
        throw std::runtime_error("runtime_error - " + std::string(e.what()));
    }
    return item;
}

void CharacterLoader::parseControllers(CharacterPOJO* item, tinyxml2::XMLElement* l_data)
{
    l_data = l_data->FirstChildElement("controller");
    while(l_data)
    {
        item->m_controllers.push_back(l_data->GetText());
        l_data = l_data->NextSiblingElement("controller");
    }
}

void CharacterLoader::parseFrames(CharacterPOJO* item, tinyxml2::XMLElement* l_data)
{
    if (!l_data){ return; }
    int frame = -1;

    tinyxml2::XMLElement* sequenceNode = l_data->FirstChildElement("sequence");
    while(sequenceNode)
    {
        std::string id = getString(sequenceNode->FirstChildElement("id"));
        std::string temp = getString(sequenceNode->FirstChildElement("frames"));

        std::vector<int> frames;
		std::stringstream keystream(temp);
        while(!keystream.eof()) {

            keystream >> frame;
            frames.push_back(frame);
        }
        item->m_frames.push_back(std::make_pair(id, frames));

        sequenceNode = sequenceNode->NextSiblingElement("sequence");
    }
}
