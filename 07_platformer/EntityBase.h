#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map.h"

enum class EntityType { Base, Enemy, Player };

enum class EntityState
{
	Idle, Walking, Jumping, Attacking, Hurt, Dying
};


struct CollisionElement
{
	CollisionElement(float arena, TileInfo* info, const sf::FloatRect& bounds)
		: m_area(arena),
		  m_tile(info),
		  m_tileBounds(bounds)
	{
	}

	float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

bool SortCollisions(const CollisionElement* a, const CollisionElement& b);

class EntityManager;
class EntityBase
{
	friend class EntityManager;

public:
	EntityBase(EntityManager* entityManager);
	virtual ~EntityBase();

	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetSize() const;
	EntityState GetState() const;
	std::string GetName() const;
	unsigned int GetId() const;
	EntityType GetType() const;

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& pos);
	void SetSize(float x, float y);
	void SetState(const EntityState& state);

	void Move(float x, float y);
	void AddVelocity(float x, float y);
	void Accelerate(float x, float y);
	void SetAcceleration(float x, float y);
	void ApplyFriction(float x, float y);
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow* window) = 0;

protected:
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();
	
	// Method for what THIS entity does TO the collider entity.
	virtual void OnEntityCollision(EntityBase* collider, bool attack) = 0;

	std::string m_name;
	EntityType m_type;
	unsigned int m_id; // Entity id in the entity manager.
	sf::Vector2f m_position; // Current position.
	sf::Vector2f m_positionOld; // Position before entity moved.
	sf::Vector2f m_velocity; // Current velocity.
	sf::Vector2f m_maxVelocity; // Maximum velocity.
	sf::Vector2f m_speed; // Value of acceleration
	sf::Vector2f m_acceleration; // Current acceleration
	sf::Vector2f m_friction; // Default friction value
	TileInfo* m_referenceTile; // Tile underneath entity.
	sf::Vector2f m_size; // Size of the collision box.
	sf::FloatRect m_AABB; // The bounding box for collisions
	EntityState m_state; // Current entity state
	// Flags for remembering axis collisions.
	bool m_collidingOnX;
	bool m_collidingOnY;

	Collisions m_collisions;
	EntityManager* m_entityManager;
};

