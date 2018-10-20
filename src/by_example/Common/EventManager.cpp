#include "EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

EventManager::~EventManager()
{
	for (auto& itr : m_bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* binding)
{
	if(m_bindings.find(binding->m_name) != m_bindings.end()) return false;

	return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto itr = m_bindings.find(name);
	if(itr == m_bindings.end()) return false;

	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::HandleEvent(sf::Event& event)
{
	for (auto& binding_itr : m_bindings)
	{
		Binding* binding = binding_itr.second;
		for (auto& event_itr : binding->m_events)
		{
			EventType sfmlEvent = static_cast<EventType>(event.type);
			if(event_itr.first != sfmlEvent) continue;;
			if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if(event_itr.second.m_code == event.key.code)
				{
					// Matching event/keystroke
					// Increase count.
					if(binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
					break;
				}
			}
			else if(sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if(event_itr.second.m_code == event.mouseButton.button)
				{
					// Matching event/keystroke
					// Increase count
					binding->m_details.m_mouse.x = event.mouseButton.x;
					binding->m_details.m_mouse.y = event.mouseButton.y;
					if(binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
					break;
				}
			}
			else
			{
				// No need for additional checking.
				if(sfmlEvent == EventType::MouseWheel)
				{
					binding->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
				}
				else if(sfmlEvent == EventType::WindowResized)
				{
					binding->m_details.m_size.x = event.size.width;
					binding->m_details.m_size.y = event.size.height;
				}
				else if(sfmlEvent == EventType::TextEntered)
				{
					binding->m_details.m_textEntered = event.text.unicode;
				}
				++(binding->c);
			}
		}
	}
}

void EventManager::Update()
{
	if(!m_hasFocus) return;
	for (auto& binding_itr : m_bindings)
	{
		Binding* binding = binding_itr.second;
		for (auto& event_itr : binding->m_events)
		{
			switch (event_itr.first)
			{
			case EventType::Keyboard: 
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_itr.second.m_code)))
				{
					if(binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
				}
				break;
			case EventType::Mouse: 
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button(event_itr.second.m_code)))
				{
					if(binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = event_itr.second.m_code;
					}
					++(binding->c);
				}
				break;
			case EventType::Joystick: 
				// Up for expansion.
				break;
			}
		}

		if(binding->m_events.size() == binding->c)
		{
			auto callback_itr = m_callbacks.find(binding->m_name);
			if(callback_itr != m_callbacks.end())
			{
				callback_itr->second(&binding->m_details);
			}
		}
		binding->c = 0;
		binding->m_details.Clear();
	}
}

void EventManager::LoadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if(!bindings.is_open())
	{
		std::cerr << "! Failed loading keys.cfg" << std::endl;
		return;
	}

	std::string line;
	while(std::getline(bindings, line))
	{
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while(!keystream.eof())
		{
			std::string keyVal;
			keystream >> keyVal;
			int start = 0;
			int end = keyVal.find(delimiter);
			if(end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(std::stoi(keyVal.substr(start, end - start)));
			int code = std::stoi(keyVal.substr(end + delimiter.length(), 
								 keyVal.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.m_code = code;

			bind->BindEvent(type, eventInfo);
		}

		if(!AddBinding(bind)) delete bind;
		bind = nullptr;
	}

	bindings.close();
}
