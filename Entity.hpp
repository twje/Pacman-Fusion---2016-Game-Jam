#ifndef _ENTITY_
#define _ENTITY_

#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"
#include "ResourceFactory.hpp"

// Forward declaration
class Map;

//*******
// Entity
//*******
class Entity
{
private:
    std::unique_ptr<EntityPOJO> m_pojo;
    sf::Sprite m_sprite;

public:
    Entity(std::string l_id)
    {
        m_pojo.reset(ResourceFactory::getEntityPojo(l_id));

        if (!ResourceManager::getInstance()->requireResource(ResourceType::TEXTURE, m_pojo.get()->m_texture))
        {
            throw std::runtime_error("runtime_error - resource does not exist");
        }
        m_sprite.setTexture(*ResourceManager::getInstance()->getResource<sf::Texture>(ResourceType::TEXTURE, m_pojo.get()->m_texture));

        setFrame(m_pojo.get()->m_startFrame);
    }

    ~Entity()
    {
        ResourceManager::getInstance()->releaseResource(ResourceType::TEXTURE, m_pojo.get()->m_texture);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    // Getters
    int getTileX(){ return m_pojo.get()->m_tileX; }
    int getTileY(){ return m_pojo.get()->m_tileY; }
    int getLayer(){ return m_pojo.get()->m_layer; }
    int getStartFrame() { return m_pojo.get()->m_startFrame; }
    sf::Sprite& getSprite(){ return m_sprite; }

    // Setters
    void setTilePos(int x, int y, int layer, Map* l_map);

    void setFrame(int frame)
    {
        int w = m_pojo.get()->m_width;
        int h = m_pojo.get()->m_height;

        int cols = m_sprite.getTexture()->getSize().x/w;
        int xIndex = (frame-1) % cols;
        int yIndex = (frame-1) / cols;

        int l = xIndex * w;
        int r = l + w;
        int t = yIndex * h;
        int b = t + h;

        sf::IntRect region(l, t, r - l, b - t);
        m_sprite.setTextureRect(region);
    }
};

#endif // _ENTITY_
