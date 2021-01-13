#include "Block.h"

/* --------------- BLOCK --------------- */

Block::Block(sf::Vector2f size, sf::Texture* texture) {
	block.setSize(size);
	block.setTexture(texture);
}

/* --------------- GROUND --------------- */

Ground::Ground(sf::Vector2f size, sf::Texture* texture) : Block(size, texture){}

void Ground::collision() {
}

void Ground::setPos(sf::Vector2f pos) {
	block.setPosition(pos);
}

void Ground::drawTo(sf::RenderWindow& window) {
	window.draw(block);
}

/* --------------- BRICK --------------- */

Brick::Brick(sf::Vector2f size, sf::Texture* texture) : Block(size, texture) {}

void Brick::collision() {
}

void Brick::setPos(sf::Vector2f pos) {
	block.setPosition(pos);
}

void Brick::drawTo(sf::RenderWindow& window) {
	window.draw(block);
}