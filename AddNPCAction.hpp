#ifndef _ADDNPCACTION_
#define _ADDNPCACTION_

#include "IAction.hpp"
#include "Common.hpp"

//*************
// AddNPCAction
//*************
class AddNPCAction: public IAction {
public:
    struct Params: public Object
    {
        Params(std::string l_def, int l_x, int l_y, int l_layer):
        m_def(l_def),
        m_x(l_x),
        m_y(l_y),
        m_layer(l_layer)
        {}
        virtual void* getSelf(){ return this; }

        std::string m_def;
        int m_x;
        int m_y;
        int m_layer;
    };

    AddNPCAction(Map* l_map, Object* l_data): IAction(l_map, l_data){}

    virtual void execute(Trigger* l_trigger, Entity* l_entity);

    static std::string getID(){ return "AddNPC"; }
};

#endif // _ADDNPCACTION_
