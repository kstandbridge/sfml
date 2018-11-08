#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"

#include <SFML/Graphics.hpp>

class State_Game : public BaseState
{
public:
	State_Game(StateManager* stateManager);

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Activate() override {}
	virtual void Deactivate() override {}
	virtual void Update(const sf::Time& time) override;
	virtual void Draw() override;

	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_increment;
};

