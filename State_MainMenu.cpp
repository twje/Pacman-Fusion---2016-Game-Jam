#include "State_MainMenu.h"
#include "StateManager.h"



State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate(){
	//GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	//gui->LoadInterface(StateType::MainMenu, "TextBox.interface", "MainMenu");
	//gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.f, 168.f));

    //std::cout << "called" << std::endl;

	/*
	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
	*/

	//m_widget = new WindowWidget("Hello", new CurvedWidgetImp("simple_panel.png", 3));
}

void State_MainMenu::OnDestroy(){
	//m_stateMgr->GetContext()->m_guiManager->RemoveInterface(StateType::MainMenu, "MainMenu");
	//EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	//eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
	//eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
}

void State_MainMenu::Activate(){

	/*
	auto& play = *m_stateMgr->GetContext()->m_guiManager->
		GetInterface(StateType::MainMenu, "MainMenu")->GetElement("Play");
	if (m_stateMgr->HasState(StateType::Game)){
		// Resume
		play.SetText("Resume");
	} else {
		// Play
		play.SetText("Play");
	}
	*/
}

void State_MainMenu::Play(EventDetails* l_details){ /*m_stateMgr->SwitchTo(StateType::Game);*/ }
void State_MainMenu::Quit(EventDetails* l_details){ /*m_stateMgr->GetContext()->m_wind->Close();*/ }
void State_MainMenu::Draw()
{

    // claim view

    //

    //sf::RenderWindow& window = *GetStateManager()->GetContext()->m_wind->GetRenderWindow();

    // Draw using window

    //m_widget->draw(window);
}
void State_MainMenu::Update(const sf::Time& l_dT){}
void State_MainMenu::Deactivate(){}
