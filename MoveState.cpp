#include "MoveState.hpp"
#include "Character.hpp"
#include "Map.hpp"

MoveState::MoveState(Character* l_character, Map* l_map):
IState(l_character, l_map),
m_entity(l_character->getEntity()),
m_character(l_character),
m_map(l_map),
m_tileWidth(l_map->getTileWidth()),
m_moveX(-1),
m_moveY(-1),
m_moveSpeed(0.2),
m_tween(0, 0, 1),
m_pixelX(0),
m_pixelY(0),
m_anim({l_character->getEntity()->getStartFrame()}, true, 0.12f)
{}

void MoveState::postInit(int l_x, int l_y)
{
    m_moveX = l_x;
    m_moveY = l_y;
}

void MoveState::enter()
{
    if (m_moveX == 1) {
        m_anim.setFrames(m_character->getAnimationSequence("right"));
        m_character->setFacing("right");
    } else if (m_moveX == -1) {
        m_anim.setFrames(m_character->getAnimationSequence("left"));
        m_character->setFacing("left");
    } else if (m_moveY == -1) {
        m_anim.setFrames(m_character->getAnimationSequence("up"));
        m_character->setFacing("up");
    } else if (m_moveY == 1) {
        m_anim.setFrames(m_character->getAnimationSequence("down"));
        m_character->setFacing("down");
    }

    sf::Vector2f pixelPos = m_entity->getSprite().getPosition();
    m_pixelX = pixelPos.x;
    m_pixelY = pixelPos.y;
    m_tween.reset(0, m_tileWidth, m_moveSpeed);

    int targetX = m_entity->getTileX() + m_moveX;
    int targetY = m_entity->getTileY() + m_moveY;

    if (m_map->isBlocked(0, targetX, targetY))
    {
        m_moveX = 0;
        m_moveY = 0;

        StateMachine* controller = m_character->getController();
        m_entity->setFrame(m_anim.getFrame());
        controller->change(m_character->getDefaultState());
    }
}

void MoveState::exit()
{
    // triiger code

    m_entity->setTilePos(m_entity->getTileX() + m_moveX, m_entity->getTileY() + m_moveY, m_entity->getLayer(), m_map);

    // On enter triger
    Trigger* trigger = m_map->getTrigger(m_entity->getTileX(), m_entity->getTileY(), m_entity->getLayer());
    if (trigger) { trigger->invokeOnEnter(m_entity); }
}

void MoveState::update(float dt)
{
    m_anim.update(dt);
    m_entity->setFrame(m_anim.getFrame());
    m_tween.update(dt);

    float value = m_tween.value();
    float x = m_pixelX + value * (float)m_moveX;
    float y = m_pixelY + value * (float)m_moveY;

    m_entity->getSprite().setPosition(std::floor(x), std::floor(y));

    if (m_tween.isFinished()) {
        StateMachine* controller = m_character->getController();
        controller->change(m_character->getDefaultState());
    }
}

void MoveState::draw(sf::RenderWindow& window){}
