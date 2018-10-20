#include "Game.h"
#include <iostream>


Game::Game()
	: m_window("04 Input and Events", sf::Vector2u(800, 600))
{
	m_texture.loadFromFile("Mushroom.png");
	m_sprite.setTexture(m_texture);
	
	auto size = m_texture.getSize();
	auto windowSize = m_window.GetWindowSize();
	m_sprite.setOrigin(float(size.x) / 2.0f, float(size.y) / 2);
	m_sprite.setPosition(float(windowSize.x) / 2, float(windowSize.y) / 2);

	m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);

	m_textBox.Setup(5, 14, 350, sf::Vector2f(255, 0));

	m_textBox.Add("Use Shift+LeftMouse to move the mushroom");
}

void Game::Update()
{
	m_window.Update();
}

void Game::MoveSprite(EventDetails* event_details)
{
	auto eventManager = m_window.GetEventManager();

	auto pos = eventManager->GetMousePos(m_window.GetRenderWindow());
	m_sprite.setPosition(float(pos.x), float(pos.y));
	m_textBox.Add("Moving sprite to X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y));
}

void Game::Render()
{
	m_window.BeginDraw();

	m_window.Draw(m_sprite);
	m_textBox.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();
}
