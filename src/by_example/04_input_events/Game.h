#pragma once
#include "Common/Window.h"
#include "Common/Textbox.h"


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

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void MoveSprite(EventDetails* event_details);

	sf::Clock m_clock;
	sf::Time m_elapsed;

	Textbox m_textBox;
};

