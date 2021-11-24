#include "WaitState.hpp"

#include "Character.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "MoveState.hpp"
#include "Common.hpp"
#include "Identifiers.hpp"

WaitState::WaitState(Character* l_character, Map* l_map):
IState(l_character, l_map),
m_entity(l_character->getEntity()),
m_character(l_character),
m_map(l_map),
m_frameResetSpeed(0.1f),
m_frameCount(0)
{}

void WaitState::exit(){}
void WaitState::enter(){ m_frameCount = 0; }
void WaitState::update(float dt)
{
    if (m_frameCount != -1) {
        m_frameCount += dt;
        if (m_frameCount >= m_frameResetSpeed) {
            m_frameCount = -1;
            m_entity->setFrame(m_entity->getStartFrame());
            m_character->setFacing("down");
        }
    }

    // Only move active pacman to move
    std::string entityId = m_character->getEntity()->getId();
    if (isPacman(entityId))
    {
        if (m_map->getContext()->m_viewPortStateID == ViewPortStateID::ACTIVE_RED && entityId != RED_PACMAN){ return; }
        if (m_map->getContext()->m_viewPortStateID == ViewPortStateID::ACTIVE_BLUE && entityId != BLUE_PACMAN){ return; }
        if (m_map->getContext()->m_viewPortStateID == ViewPortStateID::ACTIVE_GREEN && entityId != GREEN_PACMAN){ return; }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        changeStates(-1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        changeStates(1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        changeStates(0, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        changeStates(0, 1);
    }
}

void WaitState::draw(sf::RenderWindow& window){}

void WaitState::changeStates(int x, int y)
{
    StateMachine* controller = m_character->getController();

    controller->getState<MoveState>("move")->postInit(x, y);
    controller->change("move");
}
