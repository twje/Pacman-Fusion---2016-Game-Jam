#include "Map.hpp"
#include "TmxTileset.h"

void Map::draw(sf::RenderWindow& window, int layer) {
	sf::FloatRect viewSpace = getViewSpace(window);

	sf::Vector2i tileBegin(floor(viewSpace.left / m_tileWidth), floor(viewSpace.top / m_tileHeight));
	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / m_tileWidth), ceil((viewSpace.top + viewSpace.height) / m_tileHeight));

	int layerIndex = layer * 3;
	for(int x = tileBegin.x; x <= tileEnd.x; ++x){
		for(int y = tileBegin.y; y <= tileEnd.y; ++y){

            // Draw ground tile
            drawTile(window, x, y, layerIndex);

            // Draw decoration tile
            drawTile(window, x, y, layerIndex + 1);
		}
	}

	// Draw entities
	std::list<Entity*> drawList;
    if (m_entities.find(layer) != m_entities.end())
    {
        for(auto item : m_entities[layer]) {
            drawList.push_back(item.second);
        }
    }
    // sort
    //std::cout << m_entities[layer].size() << std::endl;


    for(Entity* entity : drawList) {
        entity->draw(window);
    }
}
