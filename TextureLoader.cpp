#include "tinyxml2.h"
#include "TextureLoader.hpp"
#include <string>

Object* TextureLoader::loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data)
{
    sf::Texture* texture = new sf::Texture();
    try {
        std::string l_path = l_data->FirstChildElement("path")->GetText();

        if(!texture->loadFromFile(l_basePath + l_path)) {
            delete texture;
            texture = nullptr;
            throw std::runtime_error("unable to load texture: " + l_path);
        }

    } catch (std::exception& e) {
        throw std::runtime_error("runtime_error - " + std::string(e.what()));
    }

    return new ObjectAdapter<sf::Texture>(texture);
}
