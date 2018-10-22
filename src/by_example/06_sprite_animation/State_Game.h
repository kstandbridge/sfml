#pragma once
#include "Common/BaseState.h"
#include "Common/EventManager.h"
#include "Common/SpriteSheet.h"

#include <SFML/Graphics.hpp>

class State_Game : public BaseState
{
public:
	State_Game(StateManager* stateManager);

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Activate() override {}
	virtual void Deactivate() override {}
	virtual void Update(const sf::Time time) override;
	virtual void Draw() override;

	void Attack(EventDetails* details);
	void MoveLeft(EventDetails* details);
	void MoveRight(EventDetails* details);

private:
	SpriteSheet m_spriteSheet;
	TextureManager m_textureManager;
};

