#ifndef _STATE_INSTRUCTIONS_
#define _STATE_INSTRUCTIONS_

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "BaseState.h"
#include "EventManager.h"

class State_Instructions : public BaseState{
private:
    ResourceManager* m_manager;
    sf::Sprite m_sprite;

    bool m_cntPress;
    bool m_oldPress;

public:
	State_Instructions(StateManager* l_stateManager);
	~State_Instructions();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
};

#endif // _STATE_INSTRUCTIONS_
