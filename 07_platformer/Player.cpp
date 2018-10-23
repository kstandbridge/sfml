#include "Player.h"
#include "EntityManager.h"
#include "StateManager.h"

Player::Player(EntityManager* entityManager)
	: Character(entityManager)
{
	Load("Player.char");
	m_type = EntityType::Player;

	EventManager* eventManager = m_entityManager->GetContext()->m_eventManager;
	eventManager->AddCallback<Player>(StateType::Game, "Player_MoveLeft", &Player::React, this);
	eventManager->AddCallback<Player>(StateType::Game, "Player_MoveRight", &Player::React, this);
	eventManager->AddCallback<Player>(StateType::Game, "Player_MoveJump", &Player::React, this);
	eventManager->AddCallback<Player>(StateType::Game, "Player_Attack", &Player::React, this);
}

Player::~Player()
{
	EventManager* eventManager = m_entityManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Player_MoveLeft");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveRights");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveJump");
	eventManager->RemoveCallback(StateType::Game, "Player_Attack");
}

void Player::OnEntityCollision(EntityBase* collider, bool attack)
{
	if (m_state == EntityState::Dying) return;
	if (attack)
	{
		if (m_state != EntityState::Attacking) return;
		if (!m_spriteSheet.GetCurrentAnim()->IsInAction()) return;
		if (collider->GetType() != EntityType::Enemy &&
			collider->GetType() != EntityType::Player)
		{
			return;
		}
		Character* opponent = (Character*)collider;
		opponent->GetHurt(1);
		if (m_position.x > opponent->GetPosition().x)
		{
			opponent->AddVelocity(-32, 0);
		}
		else
		{
			opponent->AddVelocity(32, 0);
		}
	}
	else
	{
		// Other behavior
	}
}

void Player::React(EventDetails* details)
{
	if (details->m_name == "Player_MoveLeft") 
	{
		Character::Move(Direction::Left);
	}
	else if (details->m_name == "Player_MoveRight")
	{
		Character::Move(Direction::Right);
	}
	else if (details->m_name == "Player_Jump")
	{
		Character::Jump();
	}
	else if (details->m_name == "Player_Attack") 
	{
		Character::Attack();
	}
}
