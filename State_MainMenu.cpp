#include "State_MainMenu.h"
#include "StateManager.h"



State_MainMenu::State_MainMenu(StateManager* l_stateManager):
BaseState(l_stateManager),
m_manager(ResourceManager::getInstance()),
m_playButtonId("playbutton.png"),
m_storyButtonId("storybutton.png")
{}

State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate()
{
    // Init textures
    sf::Vector2f winSize = sf::Vector2f(GetStateManager()->GetContext()->m_wind->GetWindowSize());
    if (!m_manager->requireResource(ResourceType::TEXTURE, m_playButtonId) )
    {
        throw std::logic_error("logic error - can't load asset: " + m_playButtonId);
    }
    if (!m_manager->requireResource(ResourceType::TEXTURE, m_storyButtonId) )
    {
        throw std::logic_error("logic error - can't load asset: " + m_storyButtonId);
    }
    sf::Texture* storyTex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, m_storyButtonId);
    sf::Texture* playTex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, m_playButtonId);

    m_storyButton.setTexture(*storyTex);
    m_playButton.setTexture(*playTex);

    m_storyButton.setOrigin(sf::Vector2f(storyTex->getSize()) * .5f);
    m_playButton.setOrigin(sf::Vector2f(playTex->getSize()) * .5f);

    // Set button position
    int yOffset = winSize.y / 2.f;
    int xOffset = winSize.x / 2.f;
    int ySpace = 30 + playTex->getSize().y;

    m_playButton.setPosition(xOffset, yOffset);
    m_storyButton.setPosition(xOffset, yOffset + ySpace);

    // Assing Callbacks
    EventManager* manager = GetStateManager()->GetContext()->m_eventManager;
    manager->AddCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::mouseClick, this);
}

void State_MainMenu::OnDestroy(){

}

void State_MainMenu::Activate(){
}

void State_MainMenu::Play(EventDetails* l_details){ /*m_stateMgr->SwitchTo(StateType::Game);*/ }
void State_MainMenu::Quit(EventDetails* l_details){ /*m_stateMgr->GetContext()->m_wind->Close();*/ }
void State_MainMenu::Draw()
{
    sf::RenderWindow* window =  GetStateManager()->GetContext()->m_wind->GetRenderWindow();

    window->draw(m_playButton);
    window->draw(m_storyButton);
}
void State_MainMenu::Update(const sf::Time& l_dT){}
void State_MainMenu::Deactivate(){}

void State_MainMenu::mouseClick(EventDetails* l_details)
{
    sf::Vector2f mousePos = GetStateManager()->GetContext()->m_wind->getMousePos();

    // Navigate to level
    if (m_playButton.getGlobalBounds().contains(mousePos))
    {
        GetStateManager()->SwitchTo(StateType::Game);
    }
    if (m_storyButton.getGlobalBounds().contains(mousePos))
    {
        GetStateManager()->SwitchTo(StateType::Story);
    }
}
