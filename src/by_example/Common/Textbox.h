#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox
{
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox() { Clear(); }

	void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void Add(std::string message);
	void Clear() { m_messages.clear(); }

	void Render(sf::RenderWindow& window);

private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};

