#pragma once
#include <SFML/Graphics.hpp>

#include "Snake.h"


class World
{
public:
	World(sf::Vector2u windowSize);
	~World() {}

	int GetBlockSize() { return m_blockSize; }

	void RespawnApple();

	void Update(Snake& player);
	void Render(sf::RenderWindow& window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;

	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];
};

