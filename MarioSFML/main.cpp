#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"
#include "Brick.h"

using namespace std;
int main()
{
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mario SFML");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);

	sf::Texture dirtTexture;
	if (!dirtTexture.loadFromFile("assets/sprites/dirt.png")) {
		std::cout << "Load failed" << std::endl;
		system("pause");
	}

	Block *brick = new Brick({ 200,200 }, &dirtTexture);
	brick->setPos({ 300, 600 });
	

    //load game -> create map

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {

				//CHANGE WINDOW
			case sf::Event::LostFocus:
				std::cout << "pouet" << std::endl;
				
				break;

				//CLOSE WINDOW
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		brick->drawTo(window);
	}

    return EXIT_SUCCESS;
}
