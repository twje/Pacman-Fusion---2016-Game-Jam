#include "State_Story.hpp"
#include "StateManager.h"

State_Story::State_Story(StateManager* l_stateManager):
BaseState(l_stateManager),
m_manager(ResourceManager::getInstance()),
m_paragaph(0),
m_chunk(0),
m_cntPress(false),
m_oldPress(false)
{}

State_Story::~State_Story(){}

void State_Story::OnCreate()
{
    // Init scroll
    sf::Vector2f winSize = sf::Vector2f(GetStateManager()->GetContext()->m_wind->GetWindowSize());
    if (!m_manager->requireResource(ResourceType::TEXTURE, "scroll.png") )
    {
        throw std::logic_error("logic error - can't load asset: scroll.png");
    }
    sf::Texture* tex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, "scroll.png");
    m_scroll.setTexture(*tex);

    float xScale = winSize.x / (float)tex->getSize().x;
    float yScale = winSize.y / (float)tex->getSize().y;
    m_scroll.scale(xScale, yScale);

    // Init font
    if (!m_manager->requireResource(ResourceType::FONT, "default") )
    {
        throw std::logic_error("logic error - can't load asset: default");
    }
    sf::Font* font = m_manager->getResource<sf::Font>(ResourceType::FONT, "default");

    std::string storyP0 = "3 years ago there was an original Pac-Man, he was lonely, so lonely. He was so lonely he started eating rubbish to see if making other people happy would make him happy. It didn't, it just made him lonlier. He was feeling so lonely that he ended up splitting his soul into 3 different parts, one with happiness, one with sadness and one that was made of metal. When they all fuse they become one big metal Pac-Man.";
    std::string storyP1 = "To fuse they need 3 Green PowerGems, 3 Blue PowerGems and 3 Red PowerGems. Only the Happy Pac-Man can get the Green PowerGems but to get the Blue and Red PowerGems. Just like the Happy Pac-Man only the Metal can get the Red PowerGems and the Sad Pac-Man can only get the Blue PowerGems but theres more to it then that, they all need to feel Passion to achieve fusion.";
    std::string storyP2 = "This is the story of the Pac-Mans achieving Passion. The Sad Pac-Man was just going around eating rubbish, like he usually would but then, there were flying drones attacking him. He thought they were trying to help him so he didn\'t think anything of it. Until they started attacking everything everywhere including Pac-Mans. To fight them they needed to fuse. They tried it failed. They continued trying until they realized they couldn\'t fuse and because of that they didn't even try to help. It was hopeless for Earth just like how hopeless there try of fusion was. They couldn\'t help Earth at least they thought they couldn't until a Person came up and wrote in binary \"Please help! We won\'t survive without you.\" So they decided to try and fuse again and again but they still had a little bit of sadness in there hearts. So they will need to eat the PowerGems to helpsave the day.";

    int width = 400;
    int lines = 15;
    int characterSize = 25;
    m_story.push_back(chunckString(storyP0, lines, width, *font, characterSize));
    m_story.push_back(chunckString(storyP1, lines, width, *font, characterSize));
    m_story.push_back(chunckString(storyP2, lines, width, *font, characterSize));

    m_text.setFont(*font);
    m_text.setCharacterSize(characterSize);
    m_text.setString(m_story[m_paragaph][m_chunk]);
    m_text.setColor(sf::Color::Blue);
    m_text.setPosition(190, 100);


}

void State_Story::OnDestroy()
{
    m_manager->releaseResource(ResourceType::TEXTURE, "scroll.png");
    m_manager->releaseResource(ResourceType::FONT, "default");
}

void State_Story::Activate() { }

void State_Story::Draw()
{
    sf::RenderWindow* window =  GetStateManager()->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_scroll);
    window->draw(m_text);
}

void State_Story::Update(const sf::Time& l_dT)
{
    m_oldPress = m_cntPress;
    m_cntPress = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (m_cntPress && !m_oldPress)
    {
        GetStateManager()->SwitchTo(StateType::MainMenu);

        // fix
        /*
        if (!isFinished())
        {
            std::cout << m_story[m_paragaph].size() << std::endl;

            if (m_chunk >= m_story[m_paragaph].size())
            {
                m_paragaph++;
                m_chunk = 0;
                m_text.setString(m_story[m_paragaph][m_chunk]);
            }
            else
            {
                m_chunk++;
                m_text.setString(m_story[m_paragaph][m_chunk]);
            }
        }
        */
    }
}

void State_Story::Deactivate(){}

bool State_Story::isFinished()
{
    if (m_paragaph >= m_story.size()){ return true; }
    if (m_chunk >= m_story[m_paragaph].size()){ return true; }

    return false;
}

std::vector<std::string> State_Story::chunckString(std::string l_string, int lines, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold)
{
    std::vector<std::string> result;
    sf::String string(l_string);

    unsigned currentOffset = 0;
    bool firstWord = true;
    std::size_t wordBegining = 0;

    int cols = 0;
    for (std::size_t pos(0); pos < string.getSize(); ++pos)
    {
        auto currentChar = string[pos];
        if (currentChar == '\n')
        {
            currentOffset = 0;
            firstWord = true;
            continue;
        }
        else if (currentChar == ' ')
        {
            wordBegining = pos;
            firstWord = false;
        }

        auto glyph = font.getGlyph(currentChar, charicterSize, bold);
        currentOffset += glyph.advance;

        if (!firstWord && currentOffset > width)
        {
              pos = wordBegining;
              string[pos] = '\n';
              firstWord = true;
              currentOffset = 0;
              cols++;

              if (cols >= lines)
              {
                  result.push_back(string.substring(0, pos));
                  string = string.substring(pos, string.getSize() - 1);
                  pos = 0;
                  l_string = sf::String(string);
              }
        }
    }

    // Final piece
    if (l_string.size() != 0)
    {
        result.push_back(string.substring(0, string.getSize() - 1));
    }
    return result;
}
