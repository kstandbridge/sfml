#pragma once
#include "Common/Window.h"
#include "World.h"

class Game
{
public:
	Game();
	~Game() {};

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow() { return &m_window; }

	sf::Time GetElapsed() { return m_clock.getElapsedTime(); }
	void RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }

private:
	void MoveMushroom();
	Window m_window;

	sf::Clock m_clock;
	float m_elapsed;

	World m_world;
	Snake m_snake;
};

