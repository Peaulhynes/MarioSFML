#include "Game.h"
#include "View.h"
#include "PauseMenu.h"
#include "Map.h"
#include "GUI.h"

Game::Game()
{
	int windowWidth = 1200;
	int windowHeight = 800;

    this->window.create(sf::VideoMode(windowWidth, windowHeight), "Mario");
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);

	loadTextures();
	loadFonts();

	this->pauseMenu = new PauseMenu(assets, this->window);
	this->map = new Map(assets, this->window);
	this->gameUi = new GUI(assets, this->window, this->map);

	this->layerBg1.setTexture(assets.getTRef("background3"));
	this->layerBg1.setScale({ (float)window.getSize().x / layerBg1.getTexture()->getSize().x, (float)window.getSize().y / layerBg1.getTexture()->getSize().y });
	this->layerBg2.setTexture(assets.getTRef("background2"));
	this->layerBg2.setScale({ (float)window.getSize().x / layerBg2.getTexture()->getSize().x, (float)window.getSize().y / layerBg2.getTexture()->getSize().y });
	this->layerBg3.setTexture(assets.getTRef("background1"));
	this->layerBg3.setScale({ (float)window.getSize().x / layerBg3.getTexture()->getSize().x, (float)window.getSize().y / layerBg3.getTexture()->getSize().y });

	this->mapView.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	this->mapView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	this->layerBg1View.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	this->layerBg1View.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));


	this->layerBg2View.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	this->layerBg2View.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	/*
	this->background.setTexture(assets.getTRef("background1"));
	this->background.setScale({ (float)window.getSize().x / background.getTexture()->getSize().x, (float)window.getSize().y / background.getTexture()->getSize().y });
	*/
}

Game::~Game()
{
	delete pauseMenu;
	delete map;
	delete gameUi;
}

void Game::loadTextures() {
	assets.loadTexture("background1", "assets/sprites/background1.png");
	assets.loadTexture("background2", "assets/sprites/background2.png");
	assets.loadTexture("background3", "assets/sprites/background3.png");
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

		//int input = -2;

		if (!pauseMenu->getActive()) {
			//input = map->player->inputProcessing(deltaTime);
			map->checkCollisions(map->player->inputProcessing(deltaTime));
		}

		/* CHANGER LES 10 EN FONCTION DE LA VITESSE DU JOUEUR */

		sf::Vector2f mapPosition(window.getSize().x / 2, window.getSize().y / 2);

		if (map->player->getX() + 10 > map->size.x - window.getSize().x / 2) {
			mapPosition.x = map->size.x - window.getSize().x / 2;
		}
		else if (map->player->getX() + 10 >= window.getSize().x / 2) {
			mapPosition.x = map->player->getX() + 10;
		}
		/*
		if (map->player->getX() + 2 > map->size.x - window.getSize().x / 2) {
			layerBg1Position.x = map->size.x - window.getSize().x / 2;
		}
		else if (map->player->getX() + 2 >= window.getSize().x / 2) {
			layerBg1Position.x = map->player->getX() + 2;
		}
*/
		mapView.setCenter(mapPosition);
		//layerBg1View.setCenter(layerBg1Position);

		window.clear();

		//Second background layer
		window.setView(layerBg3View);
		window.draw(layerBg3);

		//First background layer
		window.setView(layerBg1View);
		window.draw(layerBg1);
		
		//Map layer
		window.setView(mapView);
		map->draw(window);

		//Pause menu
		window.setView(window.getDefaultView());
		pauseMenu->draw(window);
		gameUi->draw(window);


		window.display();
    }
}

