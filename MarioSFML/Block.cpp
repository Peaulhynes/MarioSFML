#include "Block.h"

/* --------------- BLOCK --------------- */

Block::Block(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) {
	block.setSize(size);
	block.setTexture(texture);
	block.setPosition(position);
}

float Block::getX() {
	return block.getPosition().x;
}

float Block::getY() {
	return block.getPosition().y;
}

sf::FloatRect Block::getGlobalBounds() {
	return block.getGlobalBounds();
}

void Block::setPosition(sf::Vector2f position) {
	block.setPosition(position);
}

void Block::draw(sf::RenderWindow& window) {
	window.draw(block);
}

/* --------------- GROUND --------------- */

Ground::Ground(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) : Block(size, texture, position){}


/* --------------- COIN --------------- */

Coin::Coin(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) : Block(size, texture, position){}

/* --------------- FLAG --------------- */

Flag::Flag(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) : Block(size, texture, position){}