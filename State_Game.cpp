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
                new AddNPCAction::Params("hero", 1, 2, -1))
        }
    };
    //std::vector<std::pair<std::string, Object*>> wake_up;
    m_map = new Map(wake_up, Utils::GetWorkingDirectory() + "Assets/Maps/pacmanfusion.tmx");
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
    m_camera.update(l_dT.asSeconds());
}

void State_Game::Deactivate(){}

