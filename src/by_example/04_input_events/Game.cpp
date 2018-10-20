#include "Game.h"



Game::Game()
	: m_window("04 Input and Events", sf::Vector2u(640, 480))
{
}

void Game::Update()
{
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw();

	m_window.EndDraw();
}
