#ifndef _NPCSTANDSTATE_
#define _NPCSTANDSTATE_

#include "StateMachine.hpp"

// Forward declaration
class Character;
class Entity;
class Map;

//**************
// NPCStandState
//**************
class NPCStandState: public IState
{
private:
    Entity* m_entity;
    Character* m_character;
    Map* m_map;

public:
    NPCStandState(Character* l_character, Map* l_map);

    virtual void exit();
    virtual void enter();
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window);
};

#endif // _NPCSTANDSTATE_
