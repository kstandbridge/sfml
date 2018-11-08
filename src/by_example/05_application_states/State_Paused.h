#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"

#include <SFML/Graphics.hpp>

class State_Paused : public BaseState
{
public:
	State_Paused(StateManager* stateManager);

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Activate() override {}
	virtual void Deactivate() override {}
	virtual void Update(const sf::Time& time) override {}
	virtual void Draw() override;

	void Unpause(EventDetails* details);

private:
	sf::Text m_text;
	sf::Font m_font;
	sf::RectangleShape m_rect;
};

