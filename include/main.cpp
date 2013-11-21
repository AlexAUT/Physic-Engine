#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "aw/colSystem/system.hpp"

//This will hide the console for VS, in Codeblock select Gui-Application as build target
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

void initCollisionSystem(aw::col::System &sys);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	window.setVerticalSyncEnabled(true);

	aw::col::System collisionSystem;
	initCollisionSystem(collisionSystem);

	sf::Clock frameTime;
	sf::Time timeSinceLastTick;

	bool started = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A)
					collisionSystem.getObjectContainer().addDynamicObject(sf::Vector2f(30, 0), sf::Vector2f(50, 50));

				if (event.key.code == sf::Keyboard::Return)
				{
					started = true;
					frameTime.restart();
				}
			}
		}
		if (started)
		{
			timeSinceLastTick += frameTime.restart();
			while (timeSinceLastTick >= sf::seconds(1.f / 60.f))
			{
				timeSinceLastTick -= sf::seconds(1.f / 60.f);
				collisionSystem.update(sf::seconds(1.f / 60.f));
			}
		}

		window.clear();
		
		collisionSystem.getObjectContainer().drawCollisionLines(window);

		window.display();
	}
	//std::cin.get();
	return 0;
}

void initCollisionSystem(aw::col::System &sys)
{
	aw::col::ObjectContainer *container = &sys.getObjectContainer();

	container->addCollisionLine(sf::Vector2f(0, 100), sf::Vector2f(300, 300));
	container->addCollisionLine(sf::Vector2f(300, 220), sf::Vector2f(500, 140));
	container->addCollisionLine(sf::Vector2f(800, 290), sf::Vector2f(200, 400));
	container->addCollisionLine(sf::Vector2f(0, 300), sf::Vector2f(300, 550));
	container->addCollisionLine(sf::Vector2f(300, 550), sf::Vector2f(800, 300));

	container->addDynamicObject(sf::Vector2f(30, 0), sf::Vector2f(50, 50));
} 