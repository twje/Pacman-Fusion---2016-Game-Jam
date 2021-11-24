#ifndef _STATE_STORY_
#define _STATE_STORY_

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "BaseState.h"
#include "EventManager.h"
#include "Tween.hpp"

class State_Story : public BaseState{
private:
    std::vector<std::vector<std::string>> m_story;
    ResourceManager* m_manager;
    sf::Sprite m_scroll;
    int m_paragaph;
    int m_chunk;

    // Hack
    bool m_cntPress;
    bool m_oldPress;
    sf::Text m_text;

public:
	State_Story(StateManager* l_stateManager);
	~State_Story();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

private:
    std::vector<std::string> chunckString(std::string text, int lines, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold = false);

    bool isFinished();
};

#endif // _STATE_STORY_
