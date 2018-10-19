#pragma once
#include "Common/Window.h"

class Game
{
public:
	Game();
	~Game() {};

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow() { return &m_window; }

	sf::Time GetElapsed() { return m_elapsed; }
	void RestartClock() { m_elapsed = m_clock.restart(); }

private:
	void MoveMushroom();
	Window m_window;

	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;

	sf::Vector2i m_direction;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};

