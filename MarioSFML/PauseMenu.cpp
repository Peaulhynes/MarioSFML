#include "PauseMenu.h"


PauseMenu::PauseMenu(AssetsManager& assets, sf::RenderWindow& window) {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Message
	message.setString("PAUSE");
	message.setFont(assets.getFRef("minecraft"));
	message.setCharacterSize(100);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f,
						messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	
	//Active
	this->active = false;
}

PauseMenu::~PauseMenu(){}

void PauseMenu::update(int gameStatus) {
	switch (gameStatus) {
	case GameStatus::PAUSE:
		active = true;
		break;
	case GameStatus::START:
	case GameStatus::GAMEOVER:
	case GameStatus::INGAME:
	default:
		active = false;
		break;
	}
}

void PauseMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(message);
	}
}