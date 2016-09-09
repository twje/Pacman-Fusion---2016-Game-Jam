//#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Game.h"
#include "WidgetImp.hpp"

#include <SFML/Graphics.hpp>
#include "AddNPCAction.hpp"
#include "Map.hpp"

/*
TextBox* CreateFixed(int x, int y, int width, int height, std::string m_text, std::string m_avatarId = "", std::string m_title = "")
{
    int padding = 5;
    int panelTileSize = 3;
    float textScale = 1.5;

    int wrap = width - padding;
    int boundsTop = padding;
    int boundsLeft = padding;

    // Portrait
    Portrait* m_portrait = nullptr;
    if (m_avatarId != "")
    {
        m_portrait = new Portrait(m_avatarId);
        m_portrait->setWidth(std::min(width, m_portrait->getWidth()));
        m_portrait->setHeight(std::min(height, m_portrait->getHeight()));

        boundsLeft = 5 + m_portrait->getWidth() + padding * 2;
        wrap = width - boundsLeft - padding;
    }

    // Label
    Label* title = nullptr;
    if (m_title != "")
    {
        title = new Label(m_title);
        boundsTop = 5+ title->getHeight() + padding * 2;
        //title->setPosition(0, title->getPosition().y + padding);
    }

    TupleInt4 textBoxSize =
    {
        x - width/2,    // left
        x + width/2,    // right
        y - height/2,   // top
        y + height/2    // bottom
    };

    TupleInt4 textBoxBounds =
    {
        boundsLeft,     // left
        -padding,       // right
        boundsTop,     // top
        -padding         // bottom
    };

    return new TextBox(m_text, textBoxSize, textBoxBounds, m_portrait, title);
};
*/

/*
//*********
// GUI_Base
//*********
class GUI_Base
{
private:
    GUI_Base* m_owner;

    sf::Vector2f m_childPaddingTL;
    sf::Vector2f m_childPaddingBR;
    sf::Vector2f m_position;
    sf::Vector2f m_size;

public:
    virtual void addChild(GUI_Base* l_child) { throw std::logic_error("logic_error - addChild not implemented"); }

    virtual void draw(sf::RenderWindow& window) = 0;

    sf::FloatRect getDrawbleRegion()
    {
        //sf::Vector2f position = m_position;
        //while(m_owner) { position += m_owner->getPosition(); }
        //sf::FloatRect result(position + m_childPaddingTL, position + m_size - m_childPaddingTL);

        //return result;
    }

    // Getters
    sf::Vector2f getPosition(){ return m_position; }

    // Setters
    void setPosition(sf::Vector2f l_position){ m_position = l_position; }
};

//**********
// GUI_Frame
//**********
class GUI_Frame: public GUI_Base
{
private:
    CurvedWidgetImp m_frame;

public:
    GUI_Frame(std::string l_textureId, int l_tileSize):
    m_frame(l_textureId, l_tileSize)
    {
        m_frame.setWidget(this);
    }

    virtual void addChild(GUI_Base* l_child)
    {

    {
        window.draw(m_frame.getLeftEdge());
        window.draw(m_frame.getTopEdge());
        window.draw(m_frame.getRightEdge());
        window.draw(m_frame.getBottomEdge());
        window.draw(m_frame.getTopLeftCorner());
        window.draw(m_frame.getTopRightCorner());
        window.draw(m_frame.getBottomRightCorner());
        window.draw(m_frame.getBottomLeftCorner());
        window.draw(m_frame.getBody());
    }

private:

};

//********
// TextBox
//********
class TextBox: public GUI_Frame
{
private:


public:

};
*/

/*
   }

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(m_frame.getLeftEdge());
        window.draw(m_frame.getTopEdge());
        window.draw(m_frame.getRightEdge());
        window.draw(m_frame.getBottomEdge());
        window.draw(m_frame.getTopLeftCorner());
        window.draw(m_frame.getTopRightCorner());
        window.draw(m_frame.getBottomRightCorner());
        window.draw(m_frame.getBottomLeftCorner());
        window.draw(m_frame.getBody());
    }

private:

};

//********
// TextBox
//********
class TextBox: public GUI_Frame
{
private:


public:

};
*/

int main(int argc, void** argv[]) {

    /*
    Game game;
    while(!game.GetWindow()->IsDone()){
        game.Update();
        game.Render();
        game.LateUpdate();
    }
    */


    std::vector<std::pair<std::string, Object*>> wake_up
    {
        {
            std::make_pair(AddNPCAction::getID(),
                new AddNPCAction::Params("hero", 11, 3, -1))
        }
    };
    Map t_map(wake_up);

    ActionFactory factory;

    // Add triggers
    Trigger* triggerTop = new Trigger();
    triggerTop->setOnEnter(factory.getAction(TeleportAction::getID(), &t_map, new TeleportAction::Params(11, 3, 0)));
    t_map.addTrigger(triggerTop, 10, 12, 0);

    Trigger* triggerDown = new Trigger();
    triggerDown->setOnEnter(factory.getAction(TeleportAction::getID(), &t_map, new TeleportAction::Params(10, 11, 0)));
    t_map.addTrigger(triggerDown, 11, 2, 0);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::View view = window.getView();
    view.zoom(0.5f);
    view.move(-200, -200);
    window.setView(view);

    float fps = 1.f/60.f;

    //TupleInt4 textBoxSize = { 0, 400, 0, 100 };
    //TupleInt4 textBoxBounds = { 5, -0, 0, -0 };
    //TupleInt4 textBoxBounds = { 10, -10, 10, -10 };
    //TextBox box("Hello", textBoxSize, textBoxBounds, nullptr, nullptr);

    //Panel panel("simple_panel.png", 3);
    //panel.position(-10, -10, 10, 10);
    //panel.centerPosition(0, 0, 20, 20);

    //TextBox* l_box = CreateFixed(200, 100, 400, 100, "some text", "avatar.png", "Thomas");

    //SelectionParams params;
    //params.m_data = { "A", "B", "C", "D", "E", "F", "G"};
    //params.m_cols = 2;
    //Selection selection(params);

    //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    //float fps = 1.f/60.f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= fps)
        {
            clock.restart();

            window.clear();

            for(int i = 0; i < t_map.layerCount(); i++)
            {
                t_map.draw(window, i);

                for(Character* temp : t_map.getEntities())
                {
                    temp->getController()->update(fps);


                }
            }

            window.display();
        }
    }
	return 0;
}
