#ifndef _MAP_
#define _MAP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "TmxMap.h"
#include "TmxLayer.h"
#include "TmxTileLayer.h"
#include "TmxTileset.h"
#include "ActionFactory.hpp"
#include "Common.hpp"
#include "Character.hpp"
#include "Trigger.hpp"

//****
// Map
//****
class Map
{
private:
    std::map<int, std::map<int, Trigger*>> m_triggers;
    std::map<int, std::map<int, Entity*>> m_entities;
    std::list<Character*> m_npcs;
    Tmx::Map* m_map;
    int m_tileWidth;
    int m_tileHeight;
    int m_xTiles;
    int m_yTiles;
    int m_blockingTile;
    ActionFactory m_factory;

public:
    Map(std::vector<std::pair<std::string, Object*>> &l_wakeup)
    {
        m_map = new Tmx::Map();
        m_map->ParseFile("C:/Users/Thomas/Desktop/How to Make an RPG/example_1_explore/examples_explore/npc-4-solution/small_room.tmx");
        m_tileWidth = m_map->GetTileWidth();
        m_tileHeight = m_map->GetTileHeight();
        m_xTiles = m_map->GetWidth();
        m_yTiles = m_map->GetHeight();
        m_blockingTile = -1;

        for(auto item : l_wakeup)
        {
            IAction* action = m_factory.getAction(item.first, this, item.second);
            action->execute(nullptr, nullptr);
            delete action;
        }

        for(Tmx::Tileset* tileset : m_map->GetTilesets())
        {
            if (tileset->GetName() == "collision_graphic") {
                m_blockingTile = tileset->GetFirstGid();
            }
        }
    }

    std::list<Character*>& getEntities()
    {
        return m_npcs;
    }

    int layerCount() {
        if ((m_map->GetNumLayers() % 3) != 0){ throw std::runtime_error("runtime_error - # of map layers should be muliple of 3"); }

        return m_map->GetNumLayers() / 3;
    }

    void addTrigger(Trigger* trigger, int tileX, int tileY, int layer)
    {
        if (m_triggers.find(layer) == m_triggers.end()) {
            m_triggers.emplace(layer, std::map<int, Trigger*>());
        }
        auto& triggerLayer = m_triggers[layer];

        int index = coordToIndex(tileX, tileY);
        if (triggerLayer.find(index) != triggerLayer.end()) {
            throw std::logic_error("logic_error - tile is already occupied by a trigger");
        }

        triggerLayer.emplace(index, trigger);
    }

    void addNPC(Character* npc)
    {
        m_npcs.push_back(npc);
    }

    Entity* getEntity(int x, int y, int layer)
    {
        int index = cordToIndex(x, y);

        if (m_entities.find(layer) == m_entities.end()){ return nullptr; }

        std::map<int, Entity*>& entities = m_entities[layer];
        if (entities.find(index) == entities.end()){ return nullptr; }

        return entities[index];
    }

    void addEntity(Entity* entity)
    {
        int layer = entity->getLayer();
        int index = cordToIndex(entity->getTileX(), entity->getTileY());

        if (m_entities.find(layer) == m_entities.end()) {
            m_entities.emplace(layer, std::map<int, Entity*>());
        }

        std::map<int, Entity*>& entities = m_entities[layer];

        if (entities.find(index) != entities.end() && entities[index] != entity){
            throw std::logic_error("logic_error - entity already exists");
        }

        entities.emplace(index, entity);
    }

    void removeEntity(Entity* entity)
    {
        int layer = entity->getLayer();
        int index = cordToIndex(entity->getTileX(), entity->getTileY());

        if (m_entities.find(layer) == m_entities.end()) {
            throw std::logic_error("logic_error - entity does not exist");
        }

        std::map<int, Entity*>& entities = m_entities[layer];
        if (entities.find(index) == entities.end() || entities[index] != entity) {
            throw std::logic_error("logic_error - entity does not exist");
        }

        entities.erase(index);
    }

    Trigger* getTrigger(int tileX, int tileY, int layer)
    {
        if (m_triggers.find(layer) == m_triggers.end()) { return nullptr; }
        auto& triggerLayer = m_triggers[layer];

        int index = coordToIndex(tileX, tileY);
        if (triggerLayer.find(index) == triggerLayer.end()) { return nullptr; }

        return triggerLayer[index];
    }

    bool isBlocked(int layer, int tileX, int tileY)
    {
        int collisionLayer = layer * 3 + 2;

        return m_blockingTile == getTileGid(tileX, tileY, collisionLayer);
    }

    sf::Vector2i getTileFoot(int x, int y)
    {
        return sf::Vector2i(x * m_tileWidth + m_tileWidth/2, y * m_tileHeight + m_tileHeight);
    }

    int getTileWidth()
    {
        return m_map->GetTileWidth();
    }

    int coordToIndex(int x, int y)
    {
        return x + y * m_xTiles;
    }

    void draw(sf::RenderWindow& window, int l_layer);

private:
    void drawTile(sf::RenderWindow& window, int x, int y, int layer)
    {
        int id = -1;
        if ((id = getTileId(x, y, layer)) == -1){ return; }

        Tmx::Tileset* tileset = getTileTileSet(x, y, layer);
        sf::Texture* texture = tileset->getTexture();

        sf::VertexArray* quads = tileset->getVertexArray(id, x, y);

        window.draw(*quads, texture);
    }

    sf::FloatRect getViewSpace(sf::RenderWindow& window) {
        sf::Vector2f viewCenter(window.getView().getCenter());
        sf::Vector2f viewSize(window.getView().getSize());
        sf::Vector2f viewSizeHalf((int)(viewSize.x / 2), (int)(viewSize.y / 2));
        sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);

        return viewSpace;
    }

    int getTileId(int x, int y, int layer) {
        if (!isOccupiedByTile(x, y, layer)){ return -1; }

        return getTileTileLayer(layer)->GetTileId(x, y);
    }

    int getTileGid(int x, int y, int layer) {
        if (!isOccupiedByTile(x, y, layer)){ return -1; }

        return getTileTileLayer(layer)->GetTileGid(x, y);
    }

    int cordToIndex(int x, int y) {
        return x + y * m_xTiles;
    }

    bool isLayerInRange(int layer) {
        return (layer >= 0 && layer < m_map->GetNumLayers());
    }

    bool isCordInRange(int x, int y) {
        return !(x < 0 || y < 0 || x >= m_xTiles || y >= m_yTiles);
    }

    bool isOccupiedByTile(int x, int y, int layer) {
        if (!isCordInRange(x, y) || !isLayerInRange(layer)){ return false; }

        return getTileTileSet(x, y, layer) ? true : false;
    }

    Tmx::TileLayer* getTileTileLayer(int layer) {
        if (!isLayerInRange(layer)){ return nullptr; }

        Tmx::Layer* result = (Tmx::Layer*)m_map->GetLayer(layer);

        if (result->GetLayerType() != Tmx::LayerType::TMX_LAYERTYPE_TILE){ return nullptr; }

        return (Tmx::TileLayer*)result;
    }

    Tmx::Tileset* getTileTileSet(int x, int y, int layer) {
        Tmx::Layer* tileLayer = getTileTileLayer(layer);

        int tilesetIndex = -1;
        if ((tilesetIndex = ((Tmx::TileLayer*)tileLayer)->GetTileTilesetIndex(x, y)) == -1){ return nullptr; }

        return (Tmx::Tileset*)m_map->GetTileset(tilesetIndex);
    }
};

#endif // _MAP_
