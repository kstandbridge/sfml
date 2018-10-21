#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"

#include <SFML/Graphics.hpp>

class State_MainMenu : public BaseState
{
public:
	State_MainMenu(StateManager* stateManager);

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Activate() override;
	virtual void Deactivate() override {}
	virtual void Update(const sf::Time time) override {}
	virtual void Draw() override;

	void MouseClick(EventDetails* details);

private:
	sf::Text m_text;
	sf::Font m_font;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];
};

