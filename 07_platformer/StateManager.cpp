#include "StateManager.h"

StateManager::StateManager(SharedContext* sharedContext)
	:m_shared(sharedContext)
{
	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
	RegisterState<State_GameOver>(StateType::GameOver);
}

StateManager::~StateManager()
{
	for (auto& it : m_states)
	{
		it.second->OnDestroy();
		delete it.second;
	}
}

void StateManager::Update(const sf::Time time)
{
	if(m_states.empty()) return;
	if(m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while(it != m_states.begin())
		{
			if(it != m_states.end())
			{
				if(!it->second->IsTranscendent())
				{
					break;
				}
			}
			--it;
		}
		for(; it != m_states.end(); ++it)
		{
			it->second->Update(time);
		}
	}
	else
	{
		m_states.back().second->Update(time);
	}
}

void StateManager::Draw()
{
	if(m_states.empty()) return;
	if(m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while(it != m_states.begin())
		{
			if(it != m_states.end())
			{
				if(!it->second->IsTransparent())
				{
					break;
				}
			}
			--it;
		}
		for(; it != m_states.end(); ++it)
		{
			m_shared->m_window->GetRenderWindow()->setView(it->second->GetView());
			it->second->Draw();
		}
	}
	else
	{
		m_states.back().second->Draw();
	}
}

void StateManager::ProcessRequests()
{
	while(m_toRemove.begin() != m_toRemove.end())
	{
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

bool StateManager::HasState(const StateType& type)
{
	for(auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if(it->first == type)
		{
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if(removed == m_toRemove.end()) return true;
			return false;
		}
	}
	return false;
}

void StateManager::SwitchTo(const StateType& type)
{
	m_shared->m_eventManager->SetCurrentState(type);
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if(it->first == type)
		{
			m_states.back().second->Deactivate();
			StateType tmp_type = it->first;
			BaseState* tmp_state = it->second;
			m_states.erase(it);
			m_states.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			m_shared->m_window->GetRenderWindow()->setView(tmp_state->GetView());
			return;
		}
	}

	// State with type wasn't found
	if(!m_states.empty()) m_states.back().second->Deactivate();
	CreateState(type);
	m_states.back().second->Activate();
	m_shared->m_window->GetRenderWindow()->setView(m_states.back().second->GetView());
}

void StateManager::CreateState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if(newState == m_stateFactory.end()) return;
	BaseState* state = newState->second();
	state->m_view = m_shared->m_window->GetRenderWindow()->getDefaultView();
	m_states.emplace_back(type, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& type)
{
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if(it->first == type)
		{
			it->second->OnDestroy();
			delete it->second;
			m_states.erase(it);
			return;
		}
	}
}
