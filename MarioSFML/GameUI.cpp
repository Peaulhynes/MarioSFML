#include "GameUI.h"

#define BIG_FONT_SIZE 120
#define MIDDLE_FONT_SIZE 35
#define SMALL_FONT_SIZE 20

GameUI::GameUI() {
	this->active = false;
}

bool GameUI::getActive() {
	return active;
}

/* --------------- MainUI --------------- */

MainUI::MainUI(AssetsManager& assets, sf::RenderWindow& window, Map* map) : GameUI() {

	this->map = map;

	//Score
	scoreText.setString("SCORE :");
	scoreText.setFont(assets.getFRef("minecraft"));
	scoreText.setCharacterSize(MIDDLE_FONT_SIZE);
	scoreText.setPosition(sf::Vector2f(10, 10));

	//Life
	lifeText.setString("LIFE :");
	lifeText.setFont(assets.getFRef("minecraft"));
	lifeText.setCharacterSize(MIDDLE_FONT_SIZE);
	lifeText.setPosition(sf::Vector2f(10, 60));

	this->box = sf::RectangleShape(sf::Vector2f(220.f, 100.f));
	box.setPosition(sf::Vector2f(5, 5));
	box.setFillColor(sf::Color(0, 0, 0, 200));
}

void MainUI::update(int gameStatus) {
	switch (gameStatus) {
		case GameStatus::PAUSE:
		case GameStatus::INGAME:
			active = true;
			break;
		default:
			active = false;
			break;
	}
}

void MainUI::draw(sf::RenderWindow& window) {

	window.draw(box);

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
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 200));

	//Message1
	message1.setString("Press 1 or 2 to choose the map");
	message1.setFont(assets.getFRef("minecraft"));
	message1.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect1 = message1.getLocalBounds();
	message1.setOrigin(messageRect1.left + messageRect1.width / 2.0f, messageRect1.top + messageRect1.height / 2.0f);
	message1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Message
	message2.setString("Press Escape to quit");
	message2.setFont(assets.getFRef("minecraft"));
	message2.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect2 = message2.getLocalBounds();
	message2.setOrigin(messageRect2.left + messageRect2.width / 2.0f, messageRect2.top + messageRect2.height / 2.0f);
	message2.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));

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
	window.draw(overlay);
	window.draw(title);
	window.draw(message1);
	window.draw(message2);
	window.draw(credits);
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
	window.draw(overlay);
	window.draw(title);
}

/* --------------- GameOverMenu --------------- */

GameOverMenu::GameOverMenu(AssetsManager& assets, sf::RenderWindow& window) : GameUI() {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 255));

	//Title
	title.setString("GAME OVER");
	title.setFont(assets.getFRef("minecraft"));
	title.setCharacterSize(BIG_FONT_SIZE);
	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 200));

	//Message1
	message1.setString("Press Enter to restart");
	message1.setFont(assets.getFRef("minecraft"));
	message1.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect1 = message1.getLocalBounds();
	message1.setOrigin(messageRect1.left + messageRect1.width / 2.0f, messageRect1.top + messageRect1.height / 2.0f);
	message1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Message
	message2.setString("Press Escape to quit");
	message2.setFont(assets.getFRef("minecraft"));
	message2.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect2 = message2.getLocalBounds();
	message2.setOrigin(messageRect2.left + messageRect2.width / 2.0f, messageRect2.top + messageRect2.height / 2.0f);
	message2.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));

}

void GameOverMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::GAMEOVER);
}

void GameOverMenu::draw(sf::RenderWindow& window) {
	window.draw(overlay);
	window.draw(title);
	window.draw(message1);
	window.draw(message2);
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
	title.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 200));

	//Message1
	message1.setString("Press Enter to restart");
	message1.setFont(assets.getFRef("minecraft"));
	message1.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect1 = message1.getLocalBounds();
	message1.setOrigin(messageRect1.left + messageRect1.width / 2.0f, messageRect1.top + messageRect1.height / 2.0f);
	message1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Message
	message2.setString("Press Escape to quit");
	message2.setFont(assets.getFRef("minecraft"));
	message2.setCharacterSize(MIDDLE_FONT_SIZE);
	sf::FloatRect messageRect2 = message2.getLocalBounds();
	message2.setOrigin(messageRect2.left + messageRect2.width / 2.0f, messageRect2.top + messageRect2.height / 2.0f);
	message2.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));
}

void VictoryMenu::update(int gameStatus) {
	active = (gameStatus == GameStatus::VICTORY);
}

void VictoryMenu::draw(sf::RenderWindow& window) {
	window.draw(overlay);
	window.draw(title);
	window.draw(message1);
	window.draw(message2);
}