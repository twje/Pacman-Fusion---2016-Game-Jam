#pragma once
#include "BaseState.h"
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "ResourceManager.hpp"

class State_MainMenu : public BaseState{
private:
    ResourceManager* m_manager;
    sf::Sprite m_playButton;
    sf::Sprite m_storyButton;
    std::string m_playButtonId;
    std::string m_storyButtonId;

public:
	State_MainMenu(StateManager* l_stateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Play(EventDetails* l_details);
	void Quit(EventDetails* l_details);

private:
    void mouseClick(EventDetails* l_details);
};
