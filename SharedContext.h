#pragma once
#include "Window.h"
#include "EventManager.h"
#include "DebugOverlay.h"

//class Map;

struct SharedContext{
	SharedContext():
		m_wind(nullptr),
		m_eventManager(nullptr)
		{}
		//m_gameMap(nullptr){}

	Window* m_wind;
	EventManager* m_eventManager;
	//Map* m_gameMap;
	DebugOverlay m_debugOverlay;
};
