#include <SFML/Graphics.hpp>
#include <iostream>

#include "PauseMenu.h"
#include "Map.h"
#include "ErrorCodes.h"

#include "Block.h"
#include "Brick.h"
#include "Coin.h"
#include "Ground.h"
#include "Player.h"

using namespace std;

int main()
{
    int windowWidth = 1200;
    int windowHeight = 800;

	float blockSize = 40;
	const int blockPerLine = 60;

	const int groundLayers = 3;

	//WINDOW
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mario SFML");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);

	//CAMERA
	sf::View view;
	view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f screenPosition(windowWidth / 2, windowHeight / 2);

	//BACKGROUND
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/sprites/background.png", sf::IntRect(0, 0, 1200, 800))) 
		exit(LoadingCodes::BACKGROUND_CODE);
	sf::Sprite background;
	background.setTexture(backgroundTexture);
	
	//GROUND
	sf::Texture groundTexture;
	if (!groundTexture.loadFromFile("assets/sprites/dirt.png")) {
		std::cout << "Load failed" << std::endl;
		system("pause");
	}
	std::vector<Ground*> groundVector;
	for (int i = 0; i < groundLayers; i++) {
		for (int j = 0; j < blockPerLine; j++) {
			Ground* dirt = new Ground({ blockSize, blockSize }, &groundTexture);
			groundVector.push_back(dirt);
			dirt->setPos({ blockSize * j, windowHeight - blockSize * i });
		}
	}

	//PLAYER
	sf::Texture playertexture;
	if (!playertexture.loadFromFile("assets/sprites/mario.png")) {
		std::cout << "[ERROR] Load player texture failed." << std::endl;
		exit(LoadingCodes::PLAYER_CODE);
	}
	Player player({ blockSize,blockSize }, &playertexture);
	player.setPos({ blockSize, windowHeight - blockSize * groundLayers });

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
		window.setView(view);

		for (int i = 0; i < groundVector.size(); i++) {
			groundVector[i]->drawTo(window);
		}
		player.drawTo(window);
		pauseMenu.drawTo(window);

		window.setView(window.getDefaultView());

		window.display();
	}

    return EXIT_SUCCESS;
}
