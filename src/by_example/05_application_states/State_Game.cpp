#include "State_Game.h"
#include "Common/StateManager.h"
#include "Common/Window.h"


State_Game::State_Game(StateManager* stateManager)
	: BaseState(stateManager)
{
}

void State_Game::OnCreate()
{
	m_texture.loadFromFile("Mushroom.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_increment = sf::Vector2f(400.0f, 400.0f);

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_Escape");
	eventManager->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time& time)
{
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetWindowSize();
	sf::Vector2u textSize = m_texture.getSize();

	if(m_sprite.getPosition().x > windowSize.x - textSize.x && m_increment.x > 0 ||
		m_sprite.getPosition().x < 0 && m_increment.x < 0)
	{
	  m_increment.x = -m_increment.x;
	}

	if((m_sprite.getPosition().y > windowSize.y - textSize.y && m_increment.y > 0) ||
		m_sprite.getPosition().y < 0 && m_increment.y < 0)
	{
	  m_increment.y = -m_increment.y;
	}

	m_sprite.setPosition(
		m_sprite.getPosition().x + m_increment.x * time.asSeconds(),
		m_sprite.getPosition().y + m_increment.y * time.asSeconds());
}

void State_Game::Draw()
{
	m_stateManager->GetContext()->m_window->GetRenderWindow()->draw(m_sprite);
}

void State_Game::MainMenu(EventDetails* details)
{
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* details)
{
	m_stateManager->SwitchTo(StateType::Paused);
}
