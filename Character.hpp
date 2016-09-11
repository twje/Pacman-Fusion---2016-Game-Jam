#ifndef _CHARACTER_
#define _CHARACTER_

#include "StateMachine.hpp"
#include "Entity.hpp"

//**********
// Character
//**********
class Character
{
private:
    std::unique_ptr<CharacterPOJO> m_pojo;
    std::unique_ptr<Entity> m_entity;
    StateMachine m_controller;

public:
    Character(std::string l_id, Map* l_map):
    m_pojo(ResourceFactory::getCharatcerPojo(l_id))
    {
        m_entity.reset(new Entity(m_pojo.get()->m_entity));

        for(std::string state : m_pojo.get()->m_controllers)
        {
            if (!m_controller.isState(state)) {
                throw std::logic_error("logic_error - state does not exist: " + state);
            }
            m_controller.addState(state, this, l_map);
        }
        m_controller.change(m_pojo.get()->m_state);
    }

    std::string getId(){ return m_pojo.get()->m_id; }

    // Getters
    Entity* getEntity(){ return m_entity.get(); }
    StateMachine* getController(){ return &m_controller; }
    std::string getDefaultState(){ return m_pojo.get()->m_state; }

    std::vector<int> getAnimationSequence(std::string anim_id)
    {
        auto& sequences = m_pojo.get()->m_frames;
        for(auto& sequence : sequences)
        {
            if (sequence.first == anim_id)
            {
                return sequence.second;
            }
        }
        return {0};
    }

    // Setters
    void setFacing(std::string l_dir){ m_pojo.get()->m_facing = l_dir; }
};

#endif // _CHARACTER_
