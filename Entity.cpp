#include "Entity.hpp"
#include "Map.hpp"
#include "Common.hpp"

void Entity::setTilePos(int x, int y, int layer, Map* l_map)
{
    if (l_map->getEntity(m_pojo.get()->m_tileX, m_pojo.get()->m_tileY, layer) == this) {
        l_map->removeEntity(this);
    }

    // Tile already occupied
    if (l_map->getEntity(x, y, layer) != nullptr) {
        throw std::logic_error("logic_error - tile already occupied with entity");
    }

    if (x >= 0 && y >= 0) {
        m_pojo.get()->m_tileX = x;
        m_pojo.get()->m_tileY = y;
    }
    m_pojo.get()->m_layer = layer;

    l_map->addEntity(this);

    sf::Vector2i tileFoot = l_map->getTileFoot(m_pojo.get()->m_tileX, m_pojo.get()->m_tileY);

    int xPos = tileFoot.x - m_pojo.get()->m_width/2;
    int yPos = tileFoot.y - m_pojo.get()->m_height;

    m_sprite.setPosition(xPos, yPos);

    /*
    if (isPacman(getId()))
    {
        setWorldPositon(sf::Vector2f(xPos, yPos));
        m_sprite.setPosition(xPos, yPos);
    }
    else
    {
        m_sprite.setPosition(xPos, yPos);
    }
    */
}
