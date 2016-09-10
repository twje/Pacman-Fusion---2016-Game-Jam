#include "Sate_Game.hpp"
#include "StateManager.h"


State_Game::State_Game(StateManager* l_stateManager):
BaseState(l_stateManager),
m_camera(l_stateManager->GetContext(), 1.5f, 4.0f),
m_sample(64, 10, 10)
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
        if (i != 1){ continue; }

        sf::View& view = m_camera.getView(i);
        window->setView(view);

        //std::cout << view.getViewport().left << std::endl;

        m_sample.draw(*window);
    }
}

void State_Game::Update(const sf::Time& l_dT)
{

}

void State_Game::Deactivate(){}

