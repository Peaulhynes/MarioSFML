#include "View.h"

View::View(Map* map, sf::RenderWindow& window) {
	this->map = map;
	this->window = &window;
	this->view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	this->view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

}

View::~View() {

}

void View::update() {

	sf::Vector2f screenPosition(window->getSize().x / 2, window->getSize().y / 2);
	
	if (map->player->getX() + 10 < window->getSize().x / 2)
		screenPosition.x = window->getSize().x / 2;
	else if (map->player->getX() + 10 > map->size.x - window->getSize().x / 2)
		screenPosition.x = map->size.x - window->getSize().x / 2;
	else
		screenPosition.x = map->player->getX() + 10;

	view.setCenter(screenPosition);

	window->setView(view);
}