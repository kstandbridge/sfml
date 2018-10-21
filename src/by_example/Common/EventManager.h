#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,

	// Prevents clashing of identifiers
    Keyboard = sf::Event::Count + 1, Mouse, Joystick
	// anything past this point is higher then the max of sf::Event:EventType
};

struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int event) { m_code = event; }

	union // Leave room for expansion by using union
	{
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string& bindName)
		: m_name(bindName)
	{
		Clear();
	}

	std::string m_name;
	
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode; // Single key code

	void Clear()
	{
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding
{
	Binding(const std::string& name)
		: m_name(name), c(0), m_details(name)
	{
	}

	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		m_events.emplace_back(type, info);
	}

	Events m_events;
	std::string m_name;
	int c; // Count of events that are "happening"

	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;


class EventManager
{
public:
	EventManager() : m_hasFocus(true) { LoadBindings(); };
	~EventManager();

	bool AddBinding(Binding* binding);
	bool RemoveBinding(std::string name);

	void SetCurrentState(StateType state) { m_currentState = state; }
	void SetFocus(bool hasFocus) { m_hasFocus = hasFocus; }

	template<class T>
	bool AddCallback(StateType state, std::string name, void(T::*func)(EventDetails*), T* instance)
	{
		auto it = m_callbacks.emplace(state, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return it->second.emplace(name, temp).second;
	}

	bool RemoveCallback(StateType state, const std::string& name);

	void HandleEvent(sf::Event& event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr)
	{
		return window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
	}

private:
	void LoadBindings();

	StateType m_currentState;
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
};