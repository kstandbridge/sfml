#include "State_Game.h"
#include "Common/StateManager.h"
#include "Common/Window.h"

State_Game::State_Game(StateManager* stateManager)
	: BaseState(stateManager), 
	  m_spriteSheet(&m_textureManager)
{
	
}

void State_Game::OnCreate()
{
	auto windowSize = m_stateManager->GetContext()->m_window->GetWindowSize();

	m_spriteSheet.LoadSheet("Player.sheet");
	m_spriteSheet.SetDirection(Direction::Right);

	m_spriteSheet.SetSpritePosition({ 
		windowSize.x / 2.0f,
		windowSize.y / 2.0f
	});

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Game, "Player_Attack", &State_Game::Attack, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveLeft", &State_Game::MoveLeft, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveRight", &State_Game::MoveRight, this);
}

void State_Game::Attack(EventDetails* details)
{
	m_spriteSheet.SetAnimation("Attack", true, true);
}

void State_Game::MoveLeft(EventDetails* details)
{
	m_spriteSheet.SetDirection(Direction::Left);
	m_spriteSheet.SetAnimation("Walk", true, true);
}

void State_Game::MoveRight(EventDetails* details)
{
	m_spriteSheet.SetDirection(Direction::Right);
	m_spriteSheet.SetAnimation("Walk", true, true);
}

void State_Game::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Player_Attack");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveLeft");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveRight");
	m_spriteSheet.ReleaseSheet();
}

void State_Game::Update(const sf::Time& time)
{
	
	m_spriteSheet.Update(time.asSeconds());
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetWindowSize();
	
}

void State_Game::Draw()
{
	m_spriteSheet.Draw(m_stateManager->GetContext()->m_window->GetRenderWindow());
}