#ifndef _WAITSTATE_
#define _WAITSTATE_

#include "StateMachine.hpp"

// Forward declaration
class Character;
class Entity;
class Map;

//**********
// WaitState
//**********
class WaitState: public IState
{
private:
    Entity* m_entity;
    Character* m_character;
    Map* m_map;
    float m_frameResetSpeed;
    float m_frameCount;

public:
    WaitState(Character* l_character, Map* l_map);

    virtual void exit();
    virtual void enter();
    virtual void update(float dt);

    virtual void draw(sf::RenderWindow& window);

private:
    void changeStates(int x, int y);
};

#endif // _WAITSTATE_
