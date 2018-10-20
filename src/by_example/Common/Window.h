#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

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

	sf::RenderWindow* GetRenderWindow() { return &m_window; }
	sf::Vector2u GetWindowSize() { return m_window.getSize(); }

	void Draw(sf::Drawable& drawable);

	bool IsFocused();
	EventManager* GetEventManager();
	void ToggleFullscreen(EventDetails* details);
	void Close(EventDetails* details = nullptr) { m_isDone = true; }

private:
	void Setup(const std::string& title, sf::Vector2u size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;

	bool m_isDone;
	bool m_isFullscreen;

	EventManager m_eventManager;
	bool m_isFocused;
};

