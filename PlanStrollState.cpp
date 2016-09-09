#include "Entity.hpp"
#include "Character.hpp"
#include "MoveState.hpp"
#include "PlanStrollState.hpp"
#include <cstdlib>

PlanStrollState::PlanStrollState(Character* l_character, Map* l_map):
IState(l_character, l_map),
m_entity(l_character->getEntity()),
m_character(l_character),
m_map(l_map),
m_controller(m_character->getController()),
m_frameResetSpeed(0.05f),
m_frameCount(0)
{
    m_countDown = rand() % 3 + 1;
}

void PlanStrollState::enter()
{
    m_frameCount = 0;
    m_countDown = rand() % 3 + 1;
}

void PlanStrollState::exit(){}

void PlanStrollState::update(float dt)
{
    m_countDown -= dt;
    if (m_countDown <= 0)
    {
        int choice = rand() % 4 + 1;
        switch(choice)
        {
            case 1: changeToMoveState(-1, 0); break;
            case 2: changeToMoveState(1, 0); break;
            case 3: changeToMoveState(0, -1); break;
            case 4: changeToMoveState(0, 1); break;
        }
    }

    // If we're in the wait state for a few frames, reset the frame to standing
    if (m_frameCount != -1)
    {
        m_frameCount += dt;
        if (m_frameCount >= m_frameResetSpeed)
        {
            m_frameCount = -1;
            m_entity->setFrame(m_entity->getStartFrame());
            m_character->setFacing("down");
        }
    }
}

void PlanStrollState::draw(sf::RenderWindow& window){}


void PlanStrollState::changeToMoveState(int x, int y)
{
    m_controller->getState<MoveState>("move")->postInit(x, y);
    m_controller->change("move");
}
