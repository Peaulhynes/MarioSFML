#include <SFML/Graphics.hpp>
#include <iostream>

#include "PauseMenu.h"
#include "Map.h"
#include "ErrorCodes.h"

#include "Block.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"

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
	if (!groundTexture.loadFromFile("assets/sprites/ground.png")) {
		exit(LoadingCodes::GROUND_CODE);
	}
	std::vector<Ground*> groundVector;
	for (int i = 0; i < groundLayers; i++) {
		for (int j = 0; j < blockPerLine; j++) {
			Ground* dirt = new Ground({ blockSize, blockSize }, &groundTexture);
			groundVector.push_back(dirt);
			dirt->setPos({ blockSize * j, windowHeight - blockSize * i });
		}
	}

	float groundY = windowHeight - (blockSize * groundLayers);

	//ENEMIES
	sf::Texture gombaTexture;
	if (!gombaTexture.loadFromFile("assets/sprites/gomba.png")) {
		exit(LoadingCodes::GOMBA_CODE);
	}

	std::vector<Gomba*> gombaVector;
	Gomba enemy1({ blockSize, blockSize }, &gombaTexture);
	Gomba enemy2({ blockSize, blockSize }, &gombaTexture);
	Gomba enemy3({ blockSize, blockSize }, &gombaTexture);
	gombaVector.push_back(&enemy1);
	gombaVector.push_back(&enemy2);
	gombaVector.push_back(&enemy3);
	enemy1.setPos({ 300, groundY });
	enemy2.setPos({ 500, groundY });
	enemy3.setPos({ 700, groundY });

	//COINS
	sf::Texture cointexture;
	if (!cointexture.loadFromFile("assets/sprites/coin.png")) {
		exit(LoadingCodes::COIN_CODE);
	}
	std::vector<Coin*> coinVector;
	Coin coin1({ blockSize, blockSize }, &cointexture);
	Coin coin2({ blockSize, blockSize }, &cointexture);
	Coin coin3({ blockSize, blockSize }, &cointexture);
	coinVector.push_back(&coin1);
	coinVector.push_back(&coin2);
	coinVector.push_back(&coin3);
	coin1.setPos({ 200, 600 });
	coin2.setPos({ 120, 600 });
	coin3.setPos({ 400, 520 });

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
		if (!pauseMenu.getActive())
			player.inputProcessing();

		//Camera scrolling
		if (player.getX() + 10 < windowWidth / 2)
			screenPosition.x = windowWidth / 2;
		else if (player.getX() + 10 > (blockSize * blockPerLine) - windowWidth / 2)
			screenPosition.x = (blockSize * blockPerLine) - windowWidth / 2;
		else
			screenPosition.x = player.getX() + 10;

		view.setCenter(screenPosition);

		window.clear();
		window.draw(background);

		// Stuff affected by the view
		window.setView(view);

		for (int i = 0; i < groundVector.size(); i++) {
			groundVector[i]->drawTo(window);
		}

		for (int i = 0; i < gombaVector.size(); i++) {
			gombaVector[i]->drawTo(window);
		}

		for (int i = 0; i < coinVector.size(); i++) {
			coinVector[i]->drawTo(window);
		}

		player.drawTo(window);
		
	
		// Stuff not affected by the view
		window.setView(window.getDefaultView());
		pauseMenu.drawTo(window);

		window.display();
	}

    return EXIT_SUCCESS;
}
