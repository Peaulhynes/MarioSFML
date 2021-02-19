#include "GameUI.h"

#define BIG_FONT_SIZE 100
#define MIDDLE_FONT_SIZE 40
#define SMALL_FONT_SIZE 20

GameUI::GameUI() {
	this->active = false;
}

/* --------------- MainUI --------------- */

MainUI::MainUI(AssetsManager& assets, sf::RenderWindow& window, Map* map) : GameUI() {

	this->map = map;
	//Message
	scoreText.setString("SCORE :");
	scoreText.setFont(assets.getFRef("minecraft"));
	scoreText.setCharacterSize(MIDDLE_FONT_SIZE);
	scoreText.setPosition(sf::Vector2f(10, 10));
	//Life
	lifeText.setString("LIFE :");
	lifeText.setFont(assets.getFRef("minecraft"));
	lifeText.setCharacterSize(MIDDLE_FONT_SIZE);
	lifeText.setPosition(sf::Vector2f(10, 60));
}

void MainUI::update(int gameStatus) {
	switch (gameStatus) {
		case GameStatus::PAUSE:
		case GameStatus::INGAME:
		case GameStatus::VICTORY:
			active = true;
			break;
		default:
			active = false;
			break;
	}
}

void MainUI::draw(sf::RenderWindow& window) {
	if (active) {
		std::ostringstream oss;
		int score = map->player->getScore();
		oss << score;
		std::string scoreString = oss.str();

		scoreText.setString("SCORE : " + scoreString);
		window.draw(scoreText);

		std::ostringstream ossLife;
		int life = map->player->getLife();
		ossLife << life;
		std::string lifeString = ossLife.str();

		lifeText.setString("LIFE : " + lifeString);
		window.draw(lifeText);
	}
}

/* --------------- StartMenu --------------- */

StartMenu::StartMenu(AssetsManager& assets, sf::RenderWindow& window) : GameUI() {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Title
	title.setString("MAD FOREST");
	title.setFont(assets.getFRef("minecraft"));
	title.setCharacterSize(BIG_FONT_SIZE);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Message
	message.setString("Press ENTER to start");
	message.setFont(assets.getFRef("minecraft"));
	message.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));

	//Credits
	credits.setString("Credits : Pauline Wargny - Oceane Lefevre");
	credits.setFont(assets.getFRef("minecraft"));
	credits.setCharacterSize(SMALL_FONT_SIZE);
	credits.setPosition(sf::Vector2f(20, window.getSize().y - 50));
}

void StartMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::START);
}

void StartMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(title);
		window.draw(message);
		window.draw(credits);
	}
}

/* --------------- PauseMenu --------------- */

PauseMenu::PauseMenu(AssetsManager& assets, sf::RenderWindow& window) : GameUI() {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Title
	title.setString("PAUSE");
	title.setFont(assets.getFRef("minecraft"));
	title.setCharacterSize(BIG_FONT_SIZE);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
}

void PauseMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::PAUSE);
}

void PauseMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(title);
	}
}

/* --------------- GameOverMenu --------------- */

GameOverMenu::GameOverMenu(AssetsManager& assets, sf::RenderWindow& window) : GameUI() {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Title
	title.setString("GAME OVER");
	title.setFont(assets.getFRef("minecraft"));
	title.setCharacterSize(BIG_FONT_SIZE);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Message
	message.setString("Press ESCAPE to quit");
	message.setFont(assets.getFRef("minecraft"));
	message.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));

}

void GameOverMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::GAMEOVER);
}

void GameOverMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(title);
		window.draw(message);
	}
}

/* --------------- VictoryMenu --------------- */

VictoryMenu::VictoryMenu(AssetsManager& assets, sf::RenderWindow& window) : GameUI() {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Title
	title.setString("YOU WON !");
	title.setFont(assets.getFRef("minecraft"));
	title.setCharacterSize(BIG_FONT_SIZE);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
}

void VictoryMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::VICTORY);
}

void VictoryMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(title);
	}
}