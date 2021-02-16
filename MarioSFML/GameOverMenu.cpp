#include "GameOverMenu.h"


GameOverMenu::GameOverMenu(AssetsManager& assets, sf::RenderWindow& window) {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Message
	message.setString("GAME OVER");
	message.setFont(assets.getFRef("minecraft"));
	message.setCharacterSize(100);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f,
		messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	//Active
	this->active = false;
}

GameOverMenu::~GameOverMenu() {}

bool GameOverMenu::getActive() {
	return active;
}

void GameOverMenu::start() {
	active = true;
}

void GameOverMenu::end() {
	active = false;
}

void GameOverMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(message);
	}
}