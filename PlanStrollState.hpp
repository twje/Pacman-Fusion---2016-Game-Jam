#ifndef _PLANSTROLLSTATE_
#define _PLANSTROLLSTATE_

#include "StateMachine.hpp"

// Forward declaration
class Entity;
class Character;
class Map;

//****************
// PlanStrollState
//****************
class PlanStrollState: public IState
{
private:
    Entity* m_entity;
    Character* m_character;
    Map* m_map;
    StateMachine* m_controller;
    float m_frameResetSpeed;
    float m_frameCount;
    float m_countDown;

public:
    PlanStrollState(Character* l_character, Map* l_map);

    virtual void exit();
    virtual void enter();
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window);

private:
    void changeToMoveState(int x, int y);
};

#endif /* _PLANSTROLLSTATE_ */
