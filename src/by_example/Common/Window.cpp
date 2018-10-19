#include "Window.h"


Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, sf::Vector2u size)
{
	Setup(title, size);
}

Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color(64, 0, 64, 255));
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event {};
	while(m_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();
		}
	}
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::Setup(const std::string& title, sf::Vector2u size)
{
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	const auto style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}
