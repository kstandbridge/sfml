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

private:
	void MoveMushroom();
	Window m_window;

	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;

	sf::Vector2f m_direction;
};

