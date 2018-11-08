#include "State_Intro.h"
#include "Common/StateManager.h"
#include "Common/Window.h"

State_Intro::State_Intro(StateManager* stateManager)
	: BaseState(stateManager)
{
}

void State_Intro::OnCreate()
{
	m_timePassed = 0.0f;

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	m_introTexture.loadFromFile("intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f,
							m_introTexture.getSize().y / 2.0f);

	m_introSprite.setPosition(windowSize.x / 2.0f, 0);

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press Space to Continue" });
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
					 textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);
}

void State_Intro::OnDestroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Intro, "Into_Continue");
}

void State_Intro::Update(const sf::Time& time)
{
	if(m_timePassed < 5.0f) // Less than five seconds
	{
		m_timePassed += time.asSeconds();
		m_introSprite.setPosition(
			m_introSprite.getPosition().x,
			m_introSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

void State_Intro::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	window->draw(m_introSprite);
	if(m_timePassed >= 5.0f)
	{
		window->draw(m_text);
	}
}

void State_Intro::Continue(EventDetails* details)
{
	if(m_timePassed >= 5.0f)
	{
		m_stateManager->SwitchTo(StateType::MainMenu);
		m_stateManager->Remove(StateType::Intro);
	}
}
