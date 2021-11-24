#include "State_Splash.hpp"
#include "StateManager.h"

State_Splash::State_Splash(StateManager* l_stateManager):
BaseState(l_stateManager),
m_manager(ResourceManager::getInstance())
{}

State_Splash::~State_Splash(){}

void State_Splash::OnCreate()
{
    // Init slogon
    sf::Vector2f winSize = sf::Vector2f(GetStateManager()->GetContext()->m_wind->GetWindowSize());
    if (!m_manager->requireResource(ResourceType::TEXTURE, "splashscreen.png") )
    {
        throw std::logic_error("logic error - can't load asset: splashscreen.png");
    }
    sf::Texture* tex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, "splashscreen.png");
    m_logo.setTexture(*tex);
    m_logo.setOrigin(sf::Vector2f(tex->getSize()) / 2.f);
    m_logo.setPosition(winSize.x * .5f, -(tex->getSize().y * .5f));

    m_tween.reset(-(tex->getSize().y * .5f), winSize.y * .5f, 5);

    // Init font
    if (!m_manager->requireResource(ResourceType::FONT, "default") )
    {
        throw std::logic_error("logic error - can't load asset: defualt");
    }
    sf::Font* font = m_manager->getResource<sf::Font>(ResourceType::FONT, "default");
    m_text.setFont(*font);
    m_text.setColor(sf::Color::Red);
    m_text.setCharacterSize(25);
    m_text.setString("Press spacebar to continue. . .");
    m_text.setOrigin(m_text.getLocalBounds().width * .5f, 0);
    m_text.setPosition(winSize.x * .5f, 15 + winSize.y *.5f);
}

void State_Splash::OnDestroy()
{
    m_manager->releaseResource(ResourceType::TEXTURE, "splashscreen.png");
}

void State_Splash::Activate() { }

void State_Splash::Draw()
{
    sf::RenderWindow* window =  GetStateManager()->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_logo);

    if (m_tween.isFinished())
    {
        window->draw(m_text);
    }
}

void State_Splash::Update(const sf::Time& l_dT)
{
    m_tween.update(l_dT.asSeconds());
    m_logo.setPosition(m_logo.getPosition().x, m_tween.value());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_tween.isFinished())
    {
        GetStateManager()->SwitchTo(StateType::MainMenu);
    }
}

void State_Splash::Deactivate(){}


