#include "AddNPCAction.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Trigger.hpp"

void AddNPCAction::execute(Trigger* l_trigger, Entity* l_entity)
{
    Params* params = (Params*)getData();
    Character* character = new Character(params->m_def, getMap());

    int layer = (params->m_layer == -1) ? character->getEntity()->getLayer() : params->m_layer;
    int xTile = (params->m_x == -1) ? character->getEntity()->getTileX() : params->m_x;
    int yTile = (params->m_y == -1) ? character->getEntity()->getTileX() : params->m_y;

    character->getEntity()->setTilePos(xTile, yTile, layer, getMap());
    getMap()->addNPC(character);
}
