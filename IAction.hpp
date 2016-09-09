#ifndef _IACTION_
#define _IACTION_

#include <memory>

// Forward declaration
class Entity;
class Object;
class Map;
class Trigger;

//********
// Actions
//********
class IAction {
private:
    std::unique_ptr<Object> m_data;
    Map* m_map;

public:
    IAction(Map* l_map, Object* l_data):
    m_map(l_map),
    m_data(l_data)
    {}

    virtual void execute(Trigger* l_trigger, Entity* l_entity) = 0;

protected:
    // Getters
    Map* getMap(){ return m_map; }
    Object* getData(){ return m_data.get(); }
};

#endif // _IACTION_
