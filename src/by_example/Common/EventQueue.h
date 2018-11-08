#pragma once
#include <queue>

using EventId = unsigned int;

class EventQueue
{
public:
	void AddEvent(const EventId& event)
	{
		m_queue.push(event);
	}

	bool ProcessEvents(EventId& id)
	{
		if(m_queue.empty()) return false;
		id = m_queue.front();
		m_queue.pop();
		return true;
	}

	void Clear()
	{
		while(!m_queue.empty())
		{
			m_queue.pop();
		}
	}

private:
	std::queue<EventId> m_queue;
};