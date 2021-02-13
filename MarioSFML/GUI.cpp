#include "GUI.h"

GUI::GUI(AssetsManager& assets, sf::RenderWindow& window, Map *map) {

	this->map = map;
	//Message
	scoreText.setString("SCORE : 0");
	scoreText.setFont(assets.getFRef("minecraft"));
	scoreText.setCharacterSize(30);
	scoreText.setPosition(sf::Vector2f(10, 10));

}

GUI::~GUI() {}

void GUI::draw(sf::RenderWindow& window) {
	std::ostringstream oss;
	int score = map->player->getScore();
	oss << score;
	std::string scoreString = oss.str();

	scoreText.setString("SCORE : " + scoreString);
	window.draw(scoreText);
}