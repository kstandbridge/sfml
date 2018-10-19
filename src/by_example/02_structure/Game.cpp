#include "Game.h"



Game::Game()
	: m_window("02 Structure", sf::Vector2u{ 640, 480 })
{
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_direction = sf::Vector2f(0.4f, 0.4f);

	auto spriteSize = m_mushroomTexture.getSize();
	m_mushroom.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
}

void Game::HandleInput()
{
	// Do nothing, yet
}

void Game::Update()
{
	m_window.Update();
	MoveMushroom();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_window.Draw(m_mushroom);
	m_window.EndDraw();
}

void Game::MoveMushroom()
{
	auto spritePos = m_mushroom.getPosition();
	auto spriteSize = m_mushroomTexture.getSize();
	auto windowSize = m_window.GetWindowSize();

	if ((spritePos.x + (spriteSize.x / 2.0f) > windowSize.x && m_direction.x > 0) ||
		spritePos.x - (spriteSize.x / 2.0f) < 0 && m_direction.x < 0)
	{
		m_direction.x = -m_direction.x;
	}
	if ((spritePos.y + (spriteSize.y / 2.0f) > windowSize.y && m_direction.y > 0) ||
		spritePos.y - (spriteSize.y / 2.0f) < 0 && m_direction.y < 0)
	{
		m_direction.y = -m_direction.y;
	}

	m_mushroom.setPosition(spritePos + m_direction);
}
