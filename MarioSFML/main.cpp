#include <SFML/Graphics.hpp>
#include <iostream>

#include "PauseMenu.h"
#include "Map.h"
#include "ErrorCodes.h"

using namespace std;
int main()
{
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mario SFML");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);

	//BACKGROUND
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/sprites/background.png", sf::IntRect(0, 0, 1200, 800))) 
		exit(LoadingCodes::BACKGROUND_CODE);
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	
	//FONT
	sf::Font minecraft;
	minecraft.loadFromFile("assets/fonts/minecraft.ttf");


	PauseMenu pauseMenu(window, minecraft);

	while (window.isOpen()) {
		sf::Event event;

		//JUMP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
		}
		//RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			
		}
		//LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			
		}

		while (window.pollEvent(event)) {
			switch (event.type) {

			//CHANGE WINDOW
			case sf::Event::LostFocus:
				pauseMenu.start();
				break;
			//CLOSE WINDOW
			case sf::Event::Closed:
				window.close();
				break;

			//ESCAPE
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					pauseMenu.switchMode();
				}
			}
		}
		window.clear();
		window.draw(background);
		pauseMenu.drawTo(window);
		window.display();
	}

    return EXIT_SUCCESS;
}
