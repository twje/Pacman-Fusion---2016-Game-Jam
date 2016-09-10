#pragma once

#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "GameCamera.hpp"

//*************
// SampleLevel
//*************
class SampleLevel
{
private:
    sf::RectangleShape m_tile;
    int m_x;
    int m_y;
    int m_dim;

public:
    SampleLevel(int l_dim, int l_x, int l_y):
    m_dim(l_dim),
    m_x(l_x),
    m_y(l_y)
    {
        m_tile.setSize(sf::Vector2f(m_dim, m_dim));
    }

    void draw(sf::RenderWindow& window)
    {
        for(int i = 0; i < m_x; i++)
        {
            for(int j = 0; j < m_y; j++)
            {
                sf::Color tileColor = sf::Color::Transparent;
                switch((i + j) % 2)
                {
                    case 0: tileColor = sf::Color::Red; break;
                    case 1: tileColor = sf::Color::Blue; break;
                }

                // render pacman
                m_tile.setPosition(i * m_dim, j * m_dim);
                m_tile.setFillColor(tileColor);
                window.draw(m_tile);
            }
        }
    }
};


class State_Game : public BaseState{
private:
    GameCamera m_camera;
    SampleLevel m_sample;

public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
};

