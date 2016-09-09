#include "TeleportAction.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "Trigger.hpp"

void TeleportAction::execute(Trigger* l_trigger, Entity* l_entity)
{
    Params* params = (Params*)getData();
    if (params->m_layer == -1){params->m_layer = 1; }

    l_entity->setTilePos(params->m_tileX, params->m_tileY, params->m_layer, getMap());
}
