#pragma once
#include "Window.h"
#include "EventManager.h"
#include "DebugOverlay.h"
#include "Identifiers.hpp"

struct SharedContext{
	SharedContext():
		m_wind(nullptr),
		m_eventManager(nullptr)
		{}
		//m_gameMap(nullptr){}

	Window* m_wind;
	EventManager* m_eventManager;
	DebugOverlay m_debugOverlay;
    ViewPortStateID m_viewPortStateID;
};
