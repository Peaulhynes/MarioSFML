#include "Brick.h"
#include <iostream>
#include <SFML\Graphics.hpp>

Brick::Brick(sf::Vector2f size, sf::Texture* texture) : Block(size, texture){}

void Brick::collision() {
}

void Brick::setPos(sf::Vector2f pos) {
	block.setPosition(pos);
}

void Brick::drawTo(sf::RenderWindow& window) {
	window.draw(block);
}