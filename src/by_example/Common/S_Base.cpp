#include "S_Base.h"

#include "SystemManager.h"
#include <algorithm>

S_Base::S_Base(const System& id, SystemManager* systemManager)
	: m_id(id), m_systemManager(systemManager)
{
}

S_Base::~S_Base()
{
	Purge();
}

bool S_Base::AddEntity(const EntityId& entity)
{
	if(HasEntity(entity)) return false;
	m_entities.emplace_back(entity);
	return true;
}

bool S_Base::HasEntity(const EntityId& entity)
{
	return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
}

bool S_Base::RemoveEntity(const EntityId& entity)
{
	auto currentEntity = std::find_if(
		m_entities.begin(), m_entities.end(),
		[&entity](EntityId& id) { return id == entity; });
	if(currentEntity == m_entities.end()) return false;
	m_entities.erase(currentEntity);
	return true;
}

bool S_Base::FitsRequirements(const Bitmask& bits)
{
	return std::find_if(
		m_requiredComponents.begin(), m_requiredComponents.end(),
		[&bits](Bitmask& b) { return  b.Matches(bits, b.GetMask()); }) != m_requiredComponents.end();
}

void S_Base::Purge()
{
	m_entities.clear();
}
