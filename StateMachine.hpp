#ifndef _STATEMACHINE_
#define _STATEMACHINE_

#include <SFML/Graphics.hpp>
#include <memory>

// Forward declaration
class Character;
class Map;

//*******
// IState
//*******
class IState
{
private:
    Character* m_character;
    Map* m_map;

public:
    IState(Character* l_character, Map* l_map):
    m_character(l_character),
    m_map(l_map)
    {}

    // Hooks
    virtual void exit() = 0;
    virtual void enter() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // Getters
    Character* getCharacter(){ return m_character; }
    Map* getMap(){ return m_map; }
};

//**********
// NullState
//**********
class NullState: public IState
{
public:
    NullState(): IState(nullptr, nullptr){}

    virtual void exit(){}
    virtual void enter(){}
    virtual void update(float dt){}
    virtual void draw(sf::RenderWindow& window){}
};

//*************
// StateMachine
//*************
class StateMachine
{
private:
    std::map<std::string, std::function<IState*(Character*, Map*)>> m_factory;
    std::map<std::string, IState*> m_states;
    std::unique_ptr<IState> m_nullState;
    IState* m_current;

public:
    StateMachine();

    void change(std::string l_stateName);

    void update(float dt);

    virtual void draw(sf::RenderWindow& window);

    bool isState(std::string state);

    void addState(std::string state, Character* l_character, Map* l_map);

    template<class T>
    T* getState(std::string l_state) {
        if (m_states.find(l_state) == m_states.end()) {
            throw std::logic_error("logic_error - state does not exist");
        }

        T* result = dynamic_cast<T*>(m_states[l_state]);
        if (!result){ throw std::logic_error("logic_error - incorrect class passed to template argument"); }

        return result;
    }

	template<class T>
	void registerState(std::string l_state){
		m_factory[l_state] = [](Character* l_character, Map* l_map) -> IState*
		{
			return new T(l_character, l_map);
		};
	}
};

#endif // _STATEMACHINE_
