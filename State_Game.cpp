#include "Sate_Game.hpp"
#include "StateManager.h"


State_Game::State_Game(StateManager* l_stateManager):
BaseState(l_stateManager),
m_camera(l_stateManager->GetContext(), 1.5f, 4.0f),
m_sample(64, 100, 100)
{}

State_Game::~State_Game(){}

void State_Game::OnCreate(){

}

void State_Game::OnDestroy(){

}

void State_Game::Activate(){

}

void State_Game::Draw()
{
    sf::RenderWindow* window = GetStateManager()->GetContext()->m_wind->GetRenderWindow();

    for(int i = 0; i < 3; i++)
    {
        //if (i != 2){ continue; }

        sf::View& view = m_camera.getView(i);
        window->setView(view);
        m_sample.draw(*window);
    }
    m_camera.drawBorders(*window);
}

void State_Game::Update(const sf::Time& l_dT)
{
    m_camera.update(l_dT.asSeconds());
}

void State_Game::Deactivate(){}

