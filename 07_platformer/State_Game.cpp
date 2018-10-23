#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_Game::~State_Game(){}

void State_Game::OnCreate(){
	EventManager* eventManager = m_stateManager->
		GetContext()->m_eventManager;

	eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	eventManager->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);

	sf::Vector2u size = m_stateManager->GetContext()->m_window->GetWindowSize();
	m_view.setSize(size.x,size.y);
	m_view.setCenter(size.x/2,size.y/2);
	m_view.zoom(0.6f);
	m_stateManager->GetContext()->m_window->GetRenderWindow()->setView(m_view);

	m_gameMap = new Map(m_stateManager->GetContext(), this);
	m_gameMap->LoadMap("media/Maps/map1.map");
}

void State_Game::OnDestroy(){
	EventManager* evMgr = m_stateManager->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");
	evMgr->RemoveCallback(StateType::Game, "Key_O");
	
	delete m_gameMap;
	m_gameMap = nullptr;
}

void State_Game::Update(const sf::Time& l_time){
	SharedContext* context = m_stateManager->GetContext();
	EntityBase* player = context->m_entityManager->Find("Player");
	if(!player){
		std::cout << "Respawning player..." << std::endl;
		context->m_entityManager->Add(EntityType::Player,"Player");
		player = context->m_entityManager->Find("Player");
		player->SetPosition(m_gameMap->GetPlayerStart());
	} else {
		m_view.setCenter(player->GetPosition());
		context->m_window->GetRenderWindow()->setView(m_view);
	}

	sf::FloatRect viewSpace = context->m_window->GetViewSpace();
	if(viewSpace.left <= 0){
		m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	} else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size){
		m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	}

	m_gameMap->Update(l_time.asSeconds());
	m_stateManager->GetContext()->m_entityManager->Update(l_time.asSeconds());
}

void State_Game::Draw(){
	m_gameMap->Draw();
	m_stateManager->GetContext()->m_entityManager->Draw();
}

void State_Game::MainMenu(EventDetails* l_details){
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details){
	m_stateManager->SwitchTo(StateType::Paused);
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}
// Test/debug methods.
void State_Game::ToggleOverlay(EventDetails* l_details){
	m_stateManager->GetContext()->m_debugOverlay.SetDebug(!m_stateManager->GetContext()->m_debugOverlay.Debug());
}