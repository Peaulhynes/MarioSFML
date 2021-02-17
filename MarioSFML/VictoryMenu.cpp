#include "VictoryMenu.h"


VictoryMenu::VictoryMenu(AssetsManager& assets, sf::RenderWindow& window) {

	//Overlay
	this->overlay = sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

	//Message
	message.setString("VICTORY");
	message.setFont(assets.getFRef("minecraft"));
	message.setCharacterSize(100);
	sf::FloatRect messageRect = message.getLocalBounds();
	message.setOrigin(messageRect.left + messageRect.width / 2.0f,
		messageRect.top + messageRect.height / 2.0f);
	message.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));


	//Active
	this->active = false;
}

VictoryMenu::~VictoryMenu() {}

bool VictoryMenu::getActive() {
	return active;
}

void VictoryMenu::start() {
	active = true;
}

void VictoryMenu::end() {
	active = false;
}

void VictoryMenu::draw(sf::RenderWindow& window) {
	if (active) {
		window.draw(overlay);
		window.draw(message);
	}
}