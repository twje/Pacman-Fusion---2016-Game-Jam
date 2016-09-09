#ifndef _MOVESTATE_
#define _MOVESTATE_

#include "Animation.hpp"
#include "StateMachine.hpp"
#include "Tween.hpp"

// Forward declatation
class Character;
class Entity;
class Map;


//**********
// MoveState
//**********
class MoveState: public IState
{
private:
    Entity* m_entity;
    Character* m_character;
    Map* m_map;
    int m_tileWidth;
    int m_moveX;
    int m_moveY;
    float m_moveSpeed;
    Tween m_tween;
    float m_pixelX;
    float m_pixelY;
    Animation m_anim;

public:
    MoveState(Character* l_character, Map* l_map);

    void postInit(int l_x, int l_y);

    virtual void exit();
    virtual void enter();
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window);
};

#endif // _MOVESTATE_
