#pragma once
#include "Common/Window.h"
#include "Common/EventManager.h"
#include "Common/StateManager.h"
#include "Common/SharedContext.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed() { return m_elapsed; }

	Window* GetWindow() { return &m_window; }

private:
	SharedContext m_context;
	Window m_window;
	StateManager m_stateManager;

	sf::Clock m_clock;
	sf::Time m_elapsed;

	void RestartClock() { m_elapsed = m_clock.restart(); }
};

