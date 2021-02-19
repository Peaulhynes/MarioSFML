#include "Game.h"
#include "GameUI.h"
#include "Map.h"
#include "Directions.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define FAR_BACKGROUND_SPEED 10
#define NEAR_BACKGROUND_SPEED 5

Game::Game()
{
	// Window creation
    this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mad Forest");
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);

	// Assets loading
	loadTextures();
	loadFonts();
	loadMaps();

	// Game creation
	this->map = new Map(assets, this->window);

	// Widgets
	widgets.insert(std::make_pair("MainUI", new MainUI(assets, this->window, this->map)));
	widgets.insert(std::make_pair("StartMenu", new StartMenu(assets, this->window)));
	widgets.insert(std::make_pair("PauseMenu", new PauseMenu(assets, this->window)));
	widgets.insert(std::make_pair("GameOverMenu", new GameOverMenu(assets, this->window)));
	widgets.insert(std::make_pair("VictoryMenu", new VictoryMenu(assets, this->window)));

	// Views and backgrounds
	this->farBackground.first = FAR_BACKGROUND_SPEED;
	this->farBackground.second.setTexture(assets.getTRef("farBackground"));
	this->farBackground.second.setScale({ (float)window.getSize().x / farBackground.second.getTexture()->getSize().x, (float)window.getSize().y / farBackground.second.getTexture()->getSize().y });
	
	this->nearBackground.first = NEAR_BACKGROUND_SPEED;
	this->nearBackground.second.setTexture(assets.getTRef("nearBackground"));
	this->nearBackground.second.setScale({ (float)window.getSize().x / nearBackground.second.getTexture()->getSize().x, (float)window.getSize().y / nearBackground.second.getTexture()->getSize().y });
	
	this->mapView.reset(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
	this->mapView.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

	this->farBackgroundView.reset(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
	this->farBackgroundView.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

	this->nearBackgroundView.reset(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
	this->nearBackgroundView.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));

	// Game status
	this->status = GameStatus::START;
}

Game::~Game()
{
	for (auto element : widgets) {
		delete element.second;
		element.second = nullptr;
	}
	delete map;
	map = nullptr;
}

void Game::loadTextures() {
	assets.loadTexture("farBackground", "assets/sprites/farBackground.png");
	assets.loadTexture("nearBackground", "assets/sprites/nearBackground.png");
	assets.loadTexture("player", "assets/sprites/player.png");
	assets.loadTexture("ground", "assets/sprites/ground.png");
	assets.loadTexture("wolf", "assets/sprites/wolf.png");
	assets.loadTexture("coin", "assets/sprites/coin.png");
	assets.loadTexture("flagBottom", "assets/sprites/flag_bottom.png");
	assets.loadTexture("flagMiddle", "assets/sprites/flag_middle.png");
	assets.loadTexture("flagTop", "assets/sprites/flag_top.png");
}

void Game::loadFonts() {
	assets.loadFont("minecraft", "assets/fonts/minecraft.ttf");
}

void Game::loadMaps() {
	assets.loadMap("map1", "assets/maps/map1.txt");
	assets.loadMap("map2", "assets/maps/map2.txt");
}

void Game::restart() {
	delete map;
	map = new Map(assets, window);
	delete widgets.find("MainUI")->second;
	widgets.find("MainUI")->second = new MainUI(assets, this->window, this->map);
	status = GameStatus::START;
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

			// Lost focus on window
			case sf::Event::LostFocus:
				if (status == GameStatus::INGAME)
					status = GameStatus::PAUSE;
				break;

			// Close window
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:

				// Level choice in start menu
				if (status == GameStatus::START) {
					if (event.key.code == sf::Keyboard::Num1) {
						status = GameStatus::INGAME;
						map->readMap(assets, assets.getMRef("map1"));
					}
					if (event.key.code == sf::Keyboard::Num2) {
						status = GameStatus::INGAME;
						map->readMap(assets, assets.getMRef("map2"));
					}
				}

				if (event.key.code == sf::Keyboard::P) {
					if (status == GameStatus::INGAME)
						status = GameStatus::PAUSE;
					else if (status == GameStatus::PAUSE)
						status = GameStatus::INGAME;
				}

				// Escape
				if (event.key.code == sf::Keyboard::Escape) 
					window.close();
					
				if (event.key.code == sf::Keyboard::Enter) {
					if (status == GameStatus::GAMEOVER || status == GameStatus::VICTORY) {
						restart();
						status = GameStatus::START;
					}
				}
			}
		}
		// Check user input and player collisions if the game is running
		if (status == GameStatus::INGAME) 
			status = map->checkCollisions(map->player->inputProcessing(deltaTime, map->size.x - 40));

		// Update UI
		for (auto widget : widgets) 
			widget.second->update(status);

		window.clear();

		// Update views if the game started
		if (status == GameStatus::INGAME || status == GameStatus::PAUSE) {

			// Views management
			const sf::Vector2f actualPosition(trunc(map->player->getX() / WINDOW_WIDTH) * WINDOW_WIDTH, trunc(map->player->getY() / WINDOW_HEIGHT) * WINDOW_HEIGHT);
			sf::Vector2f screenCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			sf::Vector2f mapPosition(screenCenter);
			float playerX = map->player->getX();

			// Middle of map
			if (playerX > screenCenter.x && playerX < map->size.x - screenCenter.x) 
				mapPosition.x = playerX;
	
			// Extremities of map
			else {
				if (playerX >= map->size.x - screenCenter.x)
					mapPosition.x = map->size.x - screenCenter.x;
			}
		
			mapView.setCenter(mapPosition);
			nearBackgroundView.setCenter(mapPosition);
		
			//Far background layer
			window.setView(farBackgroundView);
			window.draw(farBackground.second);

			//Near background layer
			window.setView(nearBackgroundView);

			nearBackground.second.setPosition(actualPosition.x, actualPosition.y);
			window.draw(nearBackground.second);

			nearBackground.second.setPosition(actualPosition.x - WINDOW_WIDTH, actualPosition.y);
			window.draw(nearBackground.second);

			nearBackground.second.setPosition(actualPosition.x + WINDOW_WIDTH, actualPosition.y);
			window.draw(nearBackground.second);

			//Map layer
			window.setView(mapView);
			map->draw(window);
		}

		//UI
		window.setView(window.getDefaultView());
		for (auto widget : widgets) {
			if (widget.second->getActive())
				widget.second->draw(window);
		}

		window.display();
    }
}

