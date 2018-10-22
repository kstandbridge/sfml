#include "Game.h"
#include "State_Intro.h"


Game::Game()
	: m_window("07 Platformer", sf::Vector2u{ 800, 600 }), 
	  m_stateManager(&m_context)
{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();

	m_stateManager.RegisterState<State_Intro>(StateType::Intro);

	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game()
{
}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}