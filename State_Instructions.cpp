#include "State_Instructions.hpp"
#include "StateManager.h"

State_Instructions::State_Instructions(StateManager* l_stateManager):
BaseState(l_stateManager),
m_manager(ResourceManager::getInstance())
{}

State_Instructions::~State_Instructions(){}

void State_Instructions::OnCreate()
{
    // Init slogon
    sf::Vector2f winSize = sf::Vector2f(GetStateManager()->GetContext()->m_wind->GetWindowSize());
    if (!m_manager->requireResource(ResourceType::TEXTURE, "instructionpage.png") )
    {
        throw std::logic_error("logic error - can't load asset: instructionpage.png");
    }
    sf::Texture* tex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, "instructionpage.png");
    m_sprite.setTexture(*tex);
}

void State_Instructions::OnDestroy()
{

}

void State_Instructions::Activate()
{

}

void State_Instructions::Draw()
{
    sf::RenderWindow* window =  GetStateManager()->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_sprite);
}

void State_Instructions::Update(const sf::Time& l_dT)
{

}

void State_Instructions::Deactivate(){}


