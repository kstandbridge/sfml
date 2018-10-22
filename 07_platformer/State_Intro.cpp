#include "State_Intro.h"
#include "Common/StateManager.h"

State_Intro::State_Intro(StateManager* stateManager)
	: BaseState(stateManager)
{
}

void State_Intro::OnCreate()
{
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	m_introTexture.loadFromFile("intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(
		m_introTexture.getSize().x / 2.0f,
		m_introTexture.getSize().y / 2.0f);

	m_introSprite.setPosition(
		windowSize.x / 2.0f,
		windowSize.y / 2.0f);

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Intro, "Key_Escape", &State_Intro::Exit, this);
}

void State_Intro::Exit(EventDetails* eventDetails)
{
	m_stateManager->GetContext()->m_window->Close();
}

void State_Intro::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Intro, "Key_Escape");
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	window->draw(m_introSprite);
}
