#include "tinyxml2.h"
#include "FileLoader.hpp"
#include "POJO.hpp"
#include <string>

Object* FileLoader::loadResource(std::string l_id, std::string l_basePath, tinyxml2::XMLNode* l_data)
{
    FilePOJO* file = new FilePOJO();
    try {
        file->m_path = l_basePath + l_data->FirstChildElement("path")->GetText();

    } catch (std::exception& e) {
        throw std::runtime_error("runtime_error - " + std::string(e.what()));
    }

    return new ObjectAdapter<FilePOJO>(file);
}

