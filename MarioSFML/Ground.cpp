#include "Ground.h"
#include <iostream>
#include <SFML\Graphics.hpp>

Ground::Ground(sf::Vector2f size, sf::Texture* texture) : Block(size, texture) {}

void Ground::collision() {
}

void Ground::setPos(sf::Vector2f pos) {
	block.setPosition(pos);
}

void Ground::drawTo(sf::RenderWindow& window) {
	window.draw(block);
}