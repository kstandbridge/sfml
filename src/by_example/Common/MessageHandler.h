#pragma once
#include "Communicator.h"
#include "EntityMessage.h"
#include <unordered_map>

using Subscribtions = std::unordered_map<EntityMessage, Communicator>;

class MessageHandler
{
public:
	bool Subscribe(const EntityMessage& type, Observer* observer)
	{
		return m_communicators[type].AddObserver(observer);
	}

	bool Unsubscribe(const EntityMessage& type, Observer* observer)
	{
		return m_communicators[type].RemoveObserver(observer);
	}

	void Dispatch(const Message& message)
	{
		auto it = m_communicators.find((EntityMessage)message.m_type);
		if(it == m_communicators.end()) return;
		it->second.Broadcast(message);
	}

private:
	Subscribtions m_communicators;
};
