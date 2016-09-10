//#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Game.h"
#include "WidgetImp.hpp"

#include <SFML/Graphics.hpp>
#include "AddNPCAction.hpp"
#include "Map.hpp"
#include "Tween.hpp"

// tween ports

int main(int argc, void** argv[]) {

    Game game;
    while(!game.GetWindow()->IsDone()){
        game.Update();
        game.Render();
        game.LateUpdate();
    }



    /*
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
    //view.zoom(0.5f);
    //view.move(-200, -200);
    window.setView(view);

    float fps = 1.f/60.f;


    //LevelViewPort camera();
    //LevelViewPort(SharedContext* l_context, float l_scaleRatio, float l_duration)


    SampleLevel level(64, 100, 100);

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

            level.draw(window);

            for(int i = 0; i < t_map.layerCount(); i++)
            {
                //t_map.draw(window, i);

                for(Character* temp : t_map.getEntities())
                {
                    //temp->getController()->update(fps);
                }
            }
            window.display();
        }
    }
	return 0;
	*/
}
