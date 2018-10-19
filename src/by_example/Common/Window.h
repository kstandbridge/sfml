#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window(const std::string& title, sf::Vector2u size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone() { return m_isDone; }

	bool IsFullscreen() { return m_isFullscreen; }

	sf::Vector2u GetWindowSize() { return m_windowSize; }

	void ToggleFullscreen();

	void Draw(sf::Drawable& drawable);

private:
	void Setup(const std::string& title, sf::Vector2u size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;

	bool m_isDone;
	bool m_isFullscreen;
};

