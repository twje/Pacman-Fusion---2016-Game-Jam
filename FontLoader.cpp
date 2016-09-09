#include "tinyxml2.h"
#include "FontLoader.hpp"
#include <string>
#include <iostream>

Object* FontLoader::loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data)
{
    sf::Font* font = new sf::Font();
    try {
        std::string l_path = l_data->FirstChildElement("path")->GetText();

        if (!font->loadFromFile(l_basePath + l_path)) {
            delete font;
            font = nullptr;
            throw std::runtime_error("unable to load font: " + l_path);
        }
    } catch (std::exception& e) {
            throw std::runtime_error("runtime_error - " + std::string(e.what()));
    }

    return new ObjectAdapter<sf::Font>(font);
}
