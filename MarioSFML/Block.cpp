#include "Block.h"

/* --------------- BLOCK --------------- */

Block::Block(sf::Vector2f size, sf::Texture* texture) {
	block.setSize(size);
	block.setTexture(texture);
}

int Block::getX() {
	return block.getPosition().x;
}

int Block::getY() {
	return block.getPosition().y;
}

sf::FloatRect Block::getGlobalBounds() {
	return block.getGlobalBounds();
}

void Block::setPosition(sf::Vector2f pos) {
	block.setPosition(pos);
}

void Block::draw(sf::RenderWindow& window) {
	window.draw(block);
}

/* --------------- GROUND --------------- */

Ground::Ground(sf::Vector2f size, sf::Texture* texture) : Block(size, texture){}

/* --------------- BRICK --------------- */

Brick::Brick(sf::Vector2f size, sf::Texture* texture) : Block(size, texture) {}
