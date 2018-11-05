#pragma once
#include <vector>
#include <unordered_map>
#include "SharedContext.h"
#include <functional>


namespace sf {
	class Time;
}

class BaseState;

enum class StateType{ Intro = 1, MainMenu, Game, Paused, GameOver, Credits };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void Update(const sf::Time time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext() { return m_shared; }
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type) { m_toRemove.push_back(type); }

	template<class T>
	void RegisterState(const StateType& l_type){
		m_stateFactory[l_type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

private:
	void CreateState(const StateType& type);
	void RemoveState(const StateType& type);

	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};

