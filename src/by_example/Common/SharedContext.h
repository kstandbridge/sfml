#pragma once
class Window;
class EventManager;
class TextureManager;
class Map;
class SystemManager;
class EntityManager;

struct SharedContext
{
	SharedContext()
		: m_window(nullptr), 
		  m_eventManager(nullptr), 
		  m_textureManager(nullptr), 
		  m_gameMap(nullptr),
		  m_systemManager(nullptr),
		  m_entityManager(nullptr)
	{
	}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	Map* m_gameMap;
	SystemManager* m_systemManager;
	EntityManager* m_entityManager;
};
