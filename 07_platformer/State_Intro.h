#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* stateManager);
	~State_Intro() {}


	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override {}
	void Deactivate() override {}
	void Update(const sf::Time time) override {}
	void Draw() override;

	void Exit(EventDetails* eventDetails);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
};

