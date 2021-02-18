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
    this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);

	loadTextures();
	loadFonts();

	this->map = new Map(assets, this->window);
	this->startMenu = new StartMenu(assets, this->window);
	this->pauseMenu = new PauseMenu(assets, this->window);
	this->gameOverMenu = new GameOverMenu(assets, this->window);
	this->victoryMenu = new VictoryMenu(assets, this->window);
	this->mainUI = new MainUI(assets, this->window, this->map);

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

	this->status = GameStatus::START;
}

Game::~Game()
{
	delete startMenu;
	startMenu = nullptr;
	delete pauseMenu;
	pauseMenu = nullptr;
	delete gameOverMenu;
    gameOverMenu = nullptr;
	delete victoryMenu;
	victoryMenu = nullptr;
	delete mainUI;
	mainUI = nullptr;
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
				if (status == GameStatus::INGAME)
					status = GameStatus::PAUSE;
				break;

			//CLOSE WINDOW
			case sf::Event::Closed:
				window.close();
				break;

			//ESCAPE
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					switch (status) {
						case GameStatus::GAMEOVER:
						case GameStatus::START:
						case GameStatus::VICTORY:
							window.close();
							break;
						case GameStatus::INGAME:
							status = GameStatus::PAUSE;
							break;
						case GameStatus::PAUSE:
							status = GameStatus::INGAME;
							break;
						default:
							break;
					}
				}
				if (event.key.code == sf::Keyboard::Enter && status == GameStatus::START)
					status = GameStatus::INGAME;
			}
		}

		if (status == GameStatus::INGAME) {
			status = map->checkCollisions(map->player->inputProcessing(deltaTime));
		}

		startMenu->update(status);
		pauseMenu->update(status);
		gameOverMenu->update(status);
		victoryMenu->update(status);
		mainUI->update(status);

		sf::Vector2f screenCenter((float)window.getSize().x / 2, (float)window.getSize().y / 2);
		sf::Vector2f mapPosition(screenCenter);
		float playerX = map->player->getX();

		/* middle of map */
		if (playerX > screenCenter.x && playerX < map->size.x - screenCenter.x) {
			mapPosition.x = playerX + farBackground.first;
		}

		/* extremities of map */
		else {
			if (playerX >= map->size.x - screenCenter.x)
				mapPosition.x = map->size.x - screenCenter.x + 100;
		}
		
		mapView.setCenter(mapPosition);
		nearBackgroundView.setCenter(mapPosition);

		window.clear();

		//Far background layer
		window.setView(farBackgroundView);
		window.draw(farBackground.second);

		//Near background layer
		window.setView(nearBackgroundView);
		window.draw(nearBackground.second);
		
		//Map layer
		window.setView(mapView);
		map->draw(window);

		//UI
		window.setView(window.getDefaultView());
		startMenu->draw(window);
		pauseMenu->draw(window);
		gameOverMenu->draw(window);
		victoryMenu->draw(window);
		mainUI->draw(window);

		window.display();
    }
}

