#include "Game.h"
#include "PauseMenu.h"
#include "Map.h"

Game::Game()
{
	int windowWidth = 1200;
	int windowHeight = 800;

    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Mario Bros");
    this->window.setFramerateLimit(120);
    this->window.setVerticalSyncEnabled(true);

	this->view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	this->view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	loadTextures();
	loadFonts();

	this->pauseMenu = new PauseMenu(assets, this->window);
	this->map = new Map(assets, this->window);
}

Game::~Game()
{
	delete pauseMenu;
	delete map;
}

void Game::loadTextures() {
	assets.loadTexture("background", "assets/sprites/background.png");
	assets.loadTexture("player", "assets/sprites/player.png");
	assets.loadTexture("ground", "assets/sprites/ground.png");
	assets.loadTexture("gomba", "assets/sprites/gomba.png");
	assets.loadTexture("coin", "assets/sprites/coin.png");
}

void Game::loadFonts() {
	assets.loadFont("minecraft", "assets/fonts/minecraft.ttf");
}


void Game::gameLoop()
{
	sf::Vector2f screenPosition(window.getSize().x / 2, window.getSize().y / 2);

	sf::Clock clock;
    while (this->window.isOpen())
    {
		sf::Event event;
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

		while (window.pollEvent(event)) {
			switch (event.type) {

				//CHANGE WINDOW
			case sf::Event::LostFocus:
				pauseMenu->start();
				break;
				//CLOSE WINDOW
			case sf::Event::Closed:
				window.close();
				break;

			
				//ESCAPE
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					pauseMenu->switchMode();
				}
			}
		}
		if (!pauseMenu->getActive())
			map->player->inputProcessing();

		//Camera scrolling
		if (map->player->getX() + 10 < window.getSize().x / 2)
			screenPosition.x = window.getSize().x / 2;
		else if (map->player->getX() + 10 > map->size.x - window.getSize().x / 2)
			screenPosition.x = map->size.x - window.getSize().x / 2;
		else
			screenPosition.x = map->player->getX() + 10;

		view.setCenter(screenPosition);
		
		window.clear();

		// Stuff affected by the view
		window.setView(view);
		map->draw(window);

		// Stuff not affected by the view
		window.setView(window.getDefaultView());
		
		pauseMenu->draw(window);

		window.display();
    }
}

