#ifndef _POJO_
#define _POJO_

#include <vector>
#include <list>
#include <sstream>
#include "Common.hpp"

//***********
// EntityPOJO
//***********
struct EntityPOJO: public Object
{
    std::string m_id;
    std::string m_texture;
    int m_width;
    int m_height;
    int m_startFrame;
    int m_tileX;
    int m_tileY;
    int m_layer;

    virtual std::string toString() {
        std::stringstream ss;
        ss << "id: " << m_id << std::endl;
        ss << "texture: " << m_texture << std::endl;
        ss << "width: " << m_width << std::endl;
        ss << "height: " << m_height << std::endl;
        ss << "tileX: " << m_tileX << std::endl;
        ss << "tileY: " << m_tileY << std::endl;
        ss << "layer: " << m_layer << std::endl;

        return ss.str();
    }

    virtual void* getSelf(){ return this; }
};

//**************
// CharacterPOJO
//**************
struct CharacterPOJO: public Object
{
    std::string m_id;
    std::string m_entity;
    std::list<std::pair<std::string, std::vector<int>>> m_frames;
    std::list<std::string> m_controllers;
    std::string m_state;
    std::string m_facing;

    virtual void* getSelf(){ return this; }

    virtual std::string toString() {
        std::stringstream ss;
        ss << "id: " << m_id << std::endl;
        ss << "entity: " << m_entity << std::endl;
        ss << "state: " << m_state << std::endl;
        ss << "facing: " << m_facing << std::endl;
        ss << "controllers: ";
        for(auto item : m_controllers){ ss << item << ", "; }
        ss << std::endl;

        for(auto animation : m_frames) {
            ss << "Animation - " << animation.first << ": ";
            for(int frame : animation.second){
                ss << frame << ", ";
            }
            ss << std::endl;
        }

        return ss.str();
    }
};

//*********
// FilePOJO
//*********
struct FilePOJO: public Object
{
    std::string m_path;
    virtual void* getSelf(){ return this; }
    virtual std::string toString() { return ("path: " + m_path); }
};

#endif // _POJO_
