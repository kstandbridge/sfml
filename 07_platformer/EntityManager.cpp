#include "EntityManager.h"
#include "SharedContext.h"

class Player;
class Enemy;

EntityManager::EntityManager(SharedContext* context, unsigned maxEntities)
	: m_context(context), m_maxEntities(maxEntities), m_idCounter(0)
{
	LoadEnemyTypes("EnemyList.list");
	RegisterEntity<Player>(EntityType::Player);
	RegisterEntity<Enemy>(EntityType::Enemy);
}

EntityManager::~EntityManager()
{
	Purge();
}

int EntityManager::Add(const EntityType& type, const std::string& name)
{
	auto entityIt = m_entityFactory.find(type);
	if(entityIt == m_entityFactory.end()) return -1;
	EntityBase* entity = entityIt->second();
	entity->m_id = m_idCounter;
	if(name != "") entity->m_name = name;
	m_entities.emplace(m_idCounter, entity);
	if(type == EntityType::Enemy)
	{
		auto typeIt = m_enemyTypes.find(name);
		if(typeIt != m_enemyTypes.end())
		{
			Enemy* enemy = (Enemy*)entity;
			enemy->Load(typeIt->second);
		}
	}
	++m_idCounter;
	return m_idCounter - 1;
}

EntityBase* EntityManager::Find(unsigned id)
{
	auto it = m_entities.find(id);
	if(it == m_entities.end()) return nullptr;
	return it->second;
}

EntityBase* EntityManager::Find(const std::string& name)
{
	for (auto& it : m_entities)
	{
		if(it.second->GetName() == name)
		{
			return it.second;
		}
	}

	return nullptr;
}

void EntityManager::Remove(unsigned id)
{
	m_entitiesToRemove.emplace_back(id);
}

void EntityManager::Update(float deltaTime)
{
	for (auto& it : m_entities)
	{
		it.second->Update(deltaTime);
	}
	EntityCollisionCheck();
	ProcessRemovals();
}

void EntityManager::Draw()
{
	sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
	sf::FloatRect viewSpace = m_context->m_window->GetViewSpace();

	for (auto& it : m_entities)
	{
		if(!viewSpace.intersects(it.second->m_AABB)) continue;
		it.second->Draw(window);
	}
}

void EntityManager::Purge()
{
	for (auto& it : m_entities)
	{
		delete it.second;
	}
	m_entities.clear();
	m_idCounter = 0;
}

SharedContext* EntityManager::GetContext()
{
	return m_context;
}

void EntityManager::ProcessRemovals()
{
	while(m_entitiesToRemove.begin() != m_entitiesToRemove.end())
	{
		unsigned int id = m_entitiesToRemove.back();
		auto it = m_entities.find(id);
		if(it != m_entities.end())
		{
			std::cout << "Discarding entity: " << it->second->GetId() << std::endl;
			delete it->second;
			m_entities.erase(it);
		}
		m_entitiesToRemove.pop_back();
	}
}

void EntityManager::LoadEnemyTypes(const std::string& name)
{
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + std::string("media/Characters/") + name);
	if(!file.is_open())
	{
		std::cout << "! Failed loading file: " << name << std::endl;
		return;
	}
	std::string line;
	while(std::getline(file,line))
	{
		if(line[0] == '|') continue;
		std::stringstream keyStream(line);
		std::string name;
		std::string charFile;
		keyStream >> name >> charFile;
		m_enemyTypes.emplace(name, charFile);
	}
	file.close();
}

void EntityManager::EntityCollisionCheck()
{	
	// TODO Look into binary space partitioning to determine which entities to check
	if(m_entities.empty()) return;
	for (auto entity1 = m_entities.begin(); std::next(entity1) != m_entities.end(); ++entity1)
	{
		for (auto entity2 = std::next(entity1); entity2 != m_entities.end(); ++entity2)
		{
			if(entity1->first == entity2->first) continue;

			// Regular AABB bounding box collision
			if(entity1->second->m_AABB.intersects(entity2->second->m_AABB))
			{
				entity1->second->OnEntityCollision(entity2->second, false);
				entity2->second->OnEntityCollision(entity1->second, false);
			}

			EntityType type1 = entity1->second->GetType();
			EntityType type2 = entity2->second->GetType();
			if(type1 == EntityType::Player || type1 == EntityType::Enemy)
			{
				Character* c1 = (Character*)entity1->second;
				if(c1->m_attackAABB.intersects(entity2->second->m_AABB))
				{
					c1->OnEntityCollision(entity2->second, true);
				}
			}

			if(type2 == EntityType::Player || type2 == EntityType::Enemy)
			{
				Character* c2 = (Character*)entity2->second;
				if(c2->m_attackAABB.intersects(entity1->second->m_AABB))
				{
					c2->OnEntityCollision(entity1->second, true);
				}
			}
		}
	}
}
