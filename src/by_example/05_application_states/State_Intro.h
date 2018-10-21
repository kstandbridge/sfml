#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"

#include <SFML/Graphics.hpp>

class State_Intro : public BaseState
{
public:

	State_Intro(StateManager* stateManager);
	~State_Intro() {}

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Activate() override {}
	virtual void Deactivate() override {}
	virtual void Update(const sf::Time time) override;
	virtual void Draw() override;

	void Continue(EventDetails* details);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Text m_text;

	float m_timePassed;
};

