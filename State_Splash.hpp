#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "BaseState.h"
#include "EventManager.h"
#include "Tween.hpp"

class State_Splash : public BaseState{
private:
    sf::Sprite m_logo;
    ResourceManager* m_manager;
    Tween m_tween;
    sf::Text m_text;

public:
	State_Splash(StateManager* l_stateManager);
	~State_Splash();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
};


