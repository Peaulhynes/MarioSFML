#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) {

	//Overlay
	this->pauseOverlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Message
	message.setString("PAUSE");
	message.setFont(font);
	message.setCharacterSize(100);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f,
						messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	
	//Active
	this->active = false;
}

PauseMenu::~PauseMenu(){}

void PauseMenu::start() {
	active = true;
}

void PauseMenu::end() {
	active = false;
}

void PauseMenu::switchMode() {
	active = !active;
}

void PauseMenu::drawTo(sf::RenderWindow& window) {
	if (active) {
		window.draw(pauseOverlay);
		window.draw(message);
	}
}