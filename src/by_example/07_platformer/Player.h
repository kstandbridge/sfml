#pragma once
#include "Character.h"
#include "EventManager.h"

class Player : public Character
{
public:
	Player(EntityManager* entityManager);
	~Player();

	virtual void OnEntityCollision(EntityBase* collider, bool attack) override;
	void React(EventDetails* details);
};

