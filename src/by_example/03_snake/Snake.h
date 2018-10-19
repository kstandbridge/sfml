#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

struct SnakeSegment
{
	SnakeSegment(int x, int y)
		: position(x, y)
	{		
	}

	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int blockSize);
	~Snake() {};

	// Helper methods
	void SetDirection(Direction direction) { m_direction = direction; }
	Direction GetDirection() { return m_direction; }
	int GetSpeed() { return m_speed; }
	
	sf::Vector2i GetPosition();

	int GetLives() { return m_lives; }
	int GetScore() { return m_score; }

	void IncreaseScore() { m_score += 10; }
	bool HasLost() { return  m_lost; }
	void Lose() { m_lost = true; }
	void ToggleLost() { m_lost = !m_lost; }

	void Extend();	// Gow the snake
	void Reset();	// Reset to starting position

	void Move();	// Movement method
	void Tick();	// Update method
	void Cut(int segments);	// Method for cutting snake.
	void Render(sf::RenderWindow& window);

private:
	void CheckCollision();

	SnakeContainer m_snakeBody;	// Segment vector
	int m_size;	// Size of the graphics;
	Direction m_direction; // Current direction
	int m_speed;	// Speed of the snake
	int m_lives;	// Lives
	int m_score;	// Score
	bool m_lost;	// Losing state
	sf::RectangleShape m_bodyRect;	// Shape used in rendering

};

