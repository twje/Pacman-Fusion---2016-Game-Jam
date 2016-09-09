#ifndef _TRIGGER_
#define _TRIGGER_

#include "IAction.hpp"

//********
// Trigger
//********
class Trigger
{
private:
    IAction* m_onEnter;
    IAction* m_onExit;
    IAction* m_onUse;

public:
    Trigger():
    m_onEnter(nullptr),
    m_onExit(nullptr),
    m_onUse(nullptr)
    {}

    void invokeOnEnter(Entity* l_entity){
        if (m_onEnter){ m_onEnter->execute(this, l_entity); }
    }

    void invokeOnExit(Entity* l_entity){
        if (m_onExit){ m_onExit->execute(this, l_entity); }
    }

    void invokeOnUse(Entity* l_entity){
        if (m_onUse){ m_onUse->execute(this, l_entity); }
    }

    // Setters
    void setOnEnter(IAction* action){ m_onEnter = action; }
    void setOnExit(IAction* action){ m_onExit = action; }
    void setOnUse(IAction* action){ m_onUse = action; }
};

#endif // _TRIGGER_
