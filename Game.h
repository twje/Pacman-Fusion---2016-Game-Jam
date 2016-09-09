#ifndef _GAME_
#define _GAME_

#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"

class Game{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Window* GetWindow();
private:
	void RestartClock();
	sf::Clock m_clock;
	sf::Time m_elapsed;
	SharedContext m_context;
	Window m_window;
	StateManager m_stateManager;
};


#endif // _GAME_
