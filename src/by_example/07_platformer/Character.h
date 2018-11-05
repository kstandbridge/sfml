#pragma once
#include "EntityBase.h"
#include "SpriteSheet.h"

class Character : public EntityBase
{
	friend class EntityManager;
public:
	Character(EntityManager* entityManager);
	virtual ~Character();

	void Move(const Direction& direction);
	void Jump();
	void Attack();
	void GetHurt(const int damage);
	void Load(const std::string& path);
	virtual void OnEntityCollision(EntityBase* collider, bool attack) override = 0;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow* window) override;

protected:
	void UpdateAttackAABB();
	void Animate();
	SpriteSheet m_spriteSheet;
	float m_jumpVelocity;
	int m_hitPoints;
	sf::FloatRect m_attackAABB;
	sf::Vector2f m_attackAABB_offset;
};

