#pragma once
#include <vector>
#include "Observer.h"
#include <algorithm>

using ObserverContainer = std::vector<Observer*>;

class Communicator
{
public:
	~Communicator()
	{
		m_observers.clear();
	}

	bool AddObserver(Observer* observer)
	{
		if(HasObserver(observer)) return false;
		m_observers.emplace_back(observer);
		return true;
	}

	bool RemoveObserver(Observer* observer)
	{
		auto existingObserver = std::find_if(
			m_observers.begin(), m_observers.end(),
			[&observer](Observer* o) { return o == observer; });
		if(existingObserver == m_observers.end()) return false;
		m_observers.erase(existingObserver);
		return true;
	}

	bool HasObserver(Observer* observer)
	{
		return (std::find_if(
			m_observers.begin(), m_observers.end(),
			[&observer](Observer* o) { return o == observer; }) != m_observers.end());
	}

	void Broadcast(const Message& message)
	{
		for (auto& observer : m_observers)
		{
			observer->Notify(message);
		}
	}

private:
	ObserverContainer m_observers;
};