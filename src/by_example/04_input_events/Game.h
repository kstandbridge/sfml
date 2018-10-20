#pragma once
#include "Common/Window.h"


class Game
{
public:
	Game();
	~Game() {}

	void Update();
	void Render();
	Window* GetWindow() { return &m_window; }

	sf::Time GetElapsed() { return m_elapsed; }
	void RestartClock() { m_elapsed = m_clock.restart(); }

private:
	Window m_window;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};

