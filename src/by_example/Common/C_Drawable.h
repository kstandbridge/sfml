#pragma once
#include "C_Base.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class C_Drawable : public C_Base
{
public:
	C_Drawable(const Component& type) : C_Base(type) {}
	virtual ~C_Drawable() {}

	virtual void UpdatePosition(const sf::Vector2f& vec) = 0;
	virtual const sf::Vector2u& GetSize() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;

private:

};
