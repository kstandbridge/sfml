#pragma once
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "DebugOverlay.h"

class Map;

struct SharedContext
{
	SharedContext()
		: m_window(nullptr), 
		  m_eventManager(nullptr), 
		  m_textureManager(nullptr), 
		  m_entityManager(nullptr),
		  m_gameMap(nullptr)
	{
	}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	EntityManager* m_entityManager;
	Map* m_gameMap;
	
	DebugOverlay m_debugOverlay;
};
