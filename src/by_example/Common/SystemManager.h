#pragma once
#include <unordered_map>
#include "ECS_Types.h"
#include "S_Base.h"
#include "EventQueue.h"
#include "MessageHandler.h"

class Window;
using SystemContainer = std::unordered_map<System, S_Base*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

class EntityManager;
class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void SetEntityManager(EntityManager* entityManager);
	EntityManager* GetEntityManager();
	MessageHandler* GetMessageHandler();

	template<class T>
	T* GetSystem(const System& system)
	{
		auto it = m_systems->find(system);
		return (it != m_systems->end() ? dynamic_cast<T*>(it->second) : nullptr);
	}

	void AddEvent(const EntityId& entity, const EventId& event);

	void Update(float deltaTime);
	void HandleEvents();
	void Draw(Window* window, unsigned int elevation);

	void EntityModified(const EntityId& entity, const Bitmask& bits);
	void RemoveEntity(const EntityId& entity);

	void PurgeEntities();
	void PurgeSystems();

private:
	SystemContainer m_systems;
	EntityManager* m_entityManager;
	EntityEventContainer m_events;
	MessageHandler m_messages;

};

