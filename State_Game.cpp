#include "Sate_Game.hpp"
#include "StateManager.h"
#include "Utilities.h"

State_Game::State_Game(StateManager* l_stateManager):
BaseState(l_stateManager),
m_camera(l_stateManager->GetContext(), 150, 1.5f, 4.0f),
m_sample(64, 100, 100)
{}

State_Game::~State_Game(){}

void State_Game::OnCreate()
{
    std::vector<std::pair<std::string, Object*>> wake_up
    {
        {
            std::make_pair(AddNPCAction::getID(),
                new AddNPCAction::Params("blue_pacman", 1, 1, -1)),
            std::make_pair(AddNPCAction::getID(),
                new AddNPCAction::Params("red_pacman", 3, 3, -1)),
            std::make_pair(AddNPCAction::getID(),
                new AddNPCAction::Params("green_pacman", 1, 4, -1))
        }
    };
    m_map = new Map(wake_up, Utils::GetWorkingDirectory() + "Assets/Maps/pacmanfusion.tmx");


    // Keybindings
    EventManager* manager = GetStateManager()->GetContext()->m_eventManager;

    manager->AddCallback(StateType::Game, "ACTIVATE_BLUE_PORT", &State_Game::activateBluePort, this);
    manager->AddCallback(StateType::Game, "ACTIVATE_RED_PORT", &State_Game::activateRedPort, this);
    manager->AddCallback(StateType::Game, "ACTIVATE_GREEN_PORT", &State_Game::activateGreenPort, this);
}

void State_Game::OnDestroy(){

}

void State_Game::Activate()
{
    m_camera.setViewPortState(ViewPortStateID::ACTIVE_BLUE);
}

void State_Game::Draw()
{
    sf::RenderWindow* window = GetStateManager()->GetContext()->m_wind->GetRenderWindow();

    for(int i = 0; i < 3; i++)
    {
        sf::View& view = m_camera.getView(i);
        window->setView(view);

        // Remder map
        for(int i = 0; i < m_map->layerCount(); i++)
        {
            m_map->draw(*window, i);
        }
    }
    m_camera.drawBorders(*window);
}

void State_Game::Update(const sf::Time& l_dT)
{
    // Update
    for(Character* character : m_map->getEntities())
    {
        if (character->getEntity()->getId() == BLUE_PACMAN)
        {
            m_camera.setViewPosition(ViewPortID::BLUE, character->getEntity()->getSprite().getPosition());
        }
        if (character->getEntity()->getId() == RED_PACMAN)
        {
            m_camera.setViewPosition(ViewPortID::RED, character->getEntity()->getSprite().getPosition());
        }
        if (character->getEntity()->getId() == GREEN_PACMAN)
        {
            m_camera.setViewPosition(ViewPortID::GREEN, character->getEntity()->getSprite().getPosition());
        }
        character->getController()->update(l_dT.asSeconds());
    }
    m_camera.update(l_dT.asSeconds());
}

void State_Game::Deactivate(){}

void State_Game::activateBluePort(EventDetails* l_details)
{
    m_camera.setViewPortState(ViewPortStateID::ACTIVE_BLUE);
}

void State_Game::activateRedPort(EventDetails* l_details)
{
    m_camera.setViewPortState(ViewPortStateID::ACTIVE_RED);
}

void State_Game::activateGreenPort(EventDetails* l_details)
{
    m_camera.setViewPortState(ViewPortStateID::ACTIVE_GREEN);
}
