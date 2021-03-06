#include "Game.h"

Game::Game()
	: m_window("Platformer", sf::Vector2u(800, 600)),
	  m_stateManager(&m_context),
	  m_entityManager(&m_context, 100)
{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_textureManager = &m_textureManager;
	m_context.m_entityManager = &m_entityManager;

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

		if(m_context.m_debugOverlay.Debug()){
		m_context.m_debugOverlay.Draw(m_window.GetRenderWindow());
	}

	m_window.EndDraw();
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

sf::Time Game::GetElapsed()
{
	return m_clock.getElapsedTime();
}

Window* Game::GetWindow()
{
	return &m_window;
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}
