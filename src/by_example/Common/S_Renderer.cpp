#include "S_Renderer.h"
#include "SystemManager.h"
#include "C_Position.h"
#include "C_Drawable.h"
#include "C_SpriteSheet.h"

S_Renderer::S_Renderer(SystemManager* systemManager)
	: S_Base(System::Renderer, systemManager)
{
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Position);
	req.TurnOnBit((unsigned int)Component::SpriteSheet);
	m_requiredComponents.push_back(req);
	req.Clear();

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Direction_Changed, this);
}

S_Renderer::~S_Renderer()
{
}


void S_Renderer::Update(float deltaTime)
{
	EntityManager* entities = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities)
	{
		C_Position* position = entities->GetComponent<C_Position>(entity, Component::Position);
		C_Drawable* drawable = nullptr;
		if(entities->HasComponent(entity, Component::SpriteSheet))
		{
			drawable = entities->GetComponent<C_Drawable>(entity, Component::SpriteSheet);
		}
		else
		{
			continue;
		}
		drawable->UpdatePosition(position->GetPosition());
	}
}

void S_Renderer::HandleEvent(const EntityId& entity, const EntityEvent& event)
{
	if(event == EntityEvent::Moving_Left || 
		event == EntityEvent::Moving_Right ||
		event == EntityEvent::Moving_Up ||
		event == EntityEvent::Moving_Down ||
		event == EntityEvent::Elecation_Change ||
		event == EntityEvent::Spawned)
	{
		SortDrawables();
	}
}

void S_Renderer::Notify(const Message& message)
{
	if(HasEntity(message.m_receiver))
	{
		EntityMessage m = (EntityMessage)message.m_type;
		switch (m)
		{
		case EntityMessage::Direction_Changed:
			SetSheetDirection(message.m_receiver, (Direction)message.m_int);
			break;;
		}
	}
}

void S_Renderer::Render(Window* window, unsigned layer)
{
	EntityManager* entities = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities)
	{
		C_Position* position = entities->GetComponent<C_Position>(entity, Component::Position);
		if(position->GetElevation() < layer) continue;
		if(position->GetElevation() > layer) break;
		C_Drawable* drawable = nullptr;
		if(!entities->HasComponent(entity, Component::SpriteSheet))
		{
			continue;
		}
		drawable = entities->GetComponent<C_Drawable>(entity, Component::SpriteSheet);
		sf::FloatRect drawableBounds;
		drawableBounds.left = position->GetPosition().x - (drawable->GetSize().x / 2.0f);
		drawableBounds.top = position->GetPosition().y - (drawable->GetSize().y);
		drawableBounds.width = drawable->GetSize().x;
		drawableBounds.height = drawable->GetSize().y;
		if(!window->GetViewSpace().intersects(drawableBounds))
		{
			continue;
		}
		drawable->Draw(window->GetRenderWindow());
	}
}

void S_Renderer::SetSheetDirection(const EntityId& entity, const Direction& direction)
{
	EntityManager* entities = m_systemManager->GetEntityManager();
	if(!entities->HasComponent(entity, Component::SpriteSheet))
	{
		return;
	}
	C_SpriteSheet* sheet = entities->GetComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
	sheet->GetSpriteSheet()->SetDirection(direction);
}

void S_Renderer::SortDrawables()
{
	EntityManager* entityManager = m_systemManager->GetEntityManager();
	std::sort(
		m_entities.begin(), m_entities.end(),
		[entityManager](unsigned int x, unsigned int y)
		{
			auto pos1 = entityManager->GetComponent<C_Position>(x, Component::Position);
			auto pos2 = entityManager->GetComponent<C_Position>(y, Component::Position);
			if(pos1->GetElevation() == pos2->GetElevation())
			{
				return pos1->GetPosition().y < pos2->GetPosition().y;
			}
			return pos1->GetElevation() < pos2->GetElevation();
		});
}

