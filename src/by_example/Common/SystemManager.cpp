#include "SystemManager.h"
#include "EntityManager.h"
#include "S_Renderer.h"

SystemManager::SystemManager()
	: m_entityManager(nullptr)
{
	// m_systems[System::State] = new S_State(this);
	// m_systems[System::Control] = new S_Control(this);
	// m_systems[System::Movement] = new S_Movement(this);
	// m_systems[System::Collision] = new S_Collision(this);
	// m_systems[System::SheetAnimation] = new S_SheetAnimation(this);
	// m_systems[System::Renderer] = new S_Renderer(this);
}

SystemManager::~SystemManager()
{
	PurgeSystems();
}

void SystemManager::SetEntityManager(EntityManager* entityManager)
{
	if(!m_entityManager) m_entityManager = entityManager;
}

EntityManager* SystemManager::GetEntityManager()
{
	return m_entityManager;
}

MessageHandler* SystemManager::GetMessageHandler()
{
	return &m_messages;
}

void SystemManager::AddEvent(const EntityId& entity, const EventId& event)
{
	m_events[entity].AddEvent(event);
}

void SystemManager::Update(float deltaTime)
{
	for (auto& it : m_systems)
	{
		it.second->Update(deltaTime);
	}
	HandleEvents();
}

void SystemManager::HandleEvents()
{
	for (auto& event : m_events)
	{
		EventId id = 0;
		while(event.second.ProcessEvents(id))
		{
			for (auto& system : m_systems)
			{
				if(system.second->HasEntity(event.first))
				{
					system.second->HandleEvent(event.first, (EntityEvent)id);
				}
			}
		}
	}
}

void SystemManager::Draw(Window* window, unsigned elevation)
{
	auto it = m_systems.find(System::Renderer);
	if(it == m_systems.end()) return;
	S_Renderer* system = (S_Renderer*)it->second;
	system->Render(window, elevation);
}

void SystemManager::EntityModified(const EntityId& entity, const Bitmask& bits)
{
	for (auto& it : m_systems)
	{
		S_Base* system = it.second;
		if(system->FitsRequirements(bits))
		{
			if(!system->HasEntity(entity))
			{
				system->AddEntity(entity);
			}
		}
		else
		{
			if(system->HasEntity(entity))
			{
				system->RemoveEntity(entity);
			}
		}
	}
}

void SystemManager::RemoveEntity(const EntityId& entity)
{
	for (auto& system : m_systems)
	{
		system.second->RemoveEntity(entity);
	}
}

void SystemManager::PurgeEntities()
{
	for (auto& system : m_systems)
	{
		system.second->Purge();
	}
}

void SystemManager::PurgeSystems()
{
	for (auto& system : m_systems)
	{
		delete system.second;
	}
	m_systems.clear();
}
