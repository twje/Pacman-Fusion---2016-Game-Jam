#include "NPCStandState.hpp"
#include "Character.hpp"
#include "Map.hpp"

NPCStandState::NPCStandState(Character* l_character, Map* l_map):
IState(l_character, l_map),
m_entity(l_character->getEntity()),
m_character(l_character),
m_map(l_map)
{}

void NPCStandState::exit(){}
void NPCStandState::enter(){}
void NPCStandState::update(float dt){}
void NPCStandState::draw(sf::RenderWindow& window){}
