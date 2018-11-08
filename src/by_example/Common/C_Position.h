#pragma once
#include <SFML/System/Vector2.hpp>
#include "C_Base.h"

class C_Position : public C_Base
{
public:
	C_Position() : C_Base(Component::Position), m_elevation(0) {}
	~C_Position() {}


	void ReadIn(std::stringstream& stream) override
	{
		stream >> m_position.x >> m_position.y >> m_elevation;
	}

	const sf::Vector2f& GetPosition() { return m_position; }
	const sf::Vector2f& GetOldPosition() { return m_positionOld; }
	unsigned int GetElevation() { return m_elevation; }

	void SetPosition(float x, float y)
	{
		m_positionOld = m_position;
		m_position = sf::Vector2f(x, y);
	}

	void SetElevation(unsigned int elevation)
	{
		m_elevation = elevation;
	}

	void MoveBy(float x, float y)
	{
		m_positionOld = m_position;
		m_position += sf::Vector2f(x, y);
	}

	void MoveBy(const sf::Vector2f& vec)
	{
		m_positionOld = m_position;
		m_position += vec;
	}

private:
	sf::Vector2f m_position;
	sf::Vector2f m_positionOld;
	unsigned m_elevation;
};
