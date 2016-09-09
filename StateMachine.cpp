#include "StateMachine.hpp"
#include "WaitState.hpp"
#include "MoveState.hpp"
#include "NPCStandState.hpp"
#include "PlanStrollState.hpp"

StateMachine::StateMachine():
m_nullState(new NullState())
{
    registerState<WaitState>("wait");
    registerState<MoveState>("move");
    registerState<NPCStandState>("npc_stand");
    registerState<PlanStrollState>("plan_stroll");

    m_current = m_nullState.get();
}

void StateMachine::change(std::string l_stateName)
{
    if (m_states.find(l_stateName) == m_states.end()) {
        throw std::logic_error("logic_error - state must exist: " + l_stateName);
    }

    m_current->exit();
    m_current = m_states[l_stateName];
    m_current->enter();
}

void StateMachine::update(float dt){ m_current->update(dt); }

void StateMachine::draw(sf::RenderWindow& window){ m_current->draw(window); }

bool StateMachine::isState(std::string state){ return (m_factory.find(state) != m_factory.end()); }

void StateMachine::addState(std::string state, Character* l_character, Map* l_map)
{
    m_states[state] = m_factory[state](l_character, l_map);
}
