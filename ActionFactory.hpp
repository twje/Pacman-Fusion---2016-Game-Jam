#ifndef _ACTIONFACTORY_
#define _ACTIONFACTORY_

#include "IAction.hpp"
#include "AddNPCAction.hpp"
#include "TeleportAction.hpp"
#include <map>
#include <functional>

//**************
// ActionFactory
//**************
class ActionFactory
{
private:
    std::map<std::string, std::function<IAction*(Map* l_map, Object* params)>> m_factory;

public:
    ActionFactory()
    {
        RegisterAction<AddNPCAction>(AddNPCAction::getID());
        RegisterAction<TeleportAction>(TeleportAction::getID());
    }

    IAction* getAction(std::string l_id, Map* l_map, Object* params)
    {
        return m_factory[l_id](l_map, params);
    }

private:
    template<class T>
	void RegisterAction(std::string l_id){
        m_factory[l_id] = [](Map* l_map, Object* params) -> IAction*
        {
            return new T(l_map, params);
        };
	}
};

#endif // _ACTIONFACTORY_
