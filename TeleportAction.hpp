#ifndef _TELEPORTACTION_
#define _TELEPORTACTION_

#include "IAction.hpp"
#include "Common.hpp"

// Forward declaration
class Entity;

//***************
// TeleportAction
//***************
class TeleportAction: public IAction {
public:
    struct Params: public Object
    {
        Params(int l_x, int l_y, int l_layer):
        m_tileX(l_x),
        m_tileY(l_y),
        m_layer(l_layer)
        {}

        virtual void* getSelf(){ return this; }

        int m_tileX;
        int m_tileY;
        int m_layer;
    };

    TeleportAction(Map* l_map, Object* l_data): IAction(l_map, l_data){}

    virtual void execute(Trigger* l_trigger, Entity* l_entity);

    static std::string getID(){ return "Teleport"; }
};

#endif // _TELEPORTACTION_
