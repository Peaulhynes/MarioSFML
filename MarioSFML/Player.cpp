#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Texture* texture) {
    player.setSize(size);
    player.setTexture(texture);
	this->moveSpeed = 5.f;
	this->isJumping = false;
}

void Player::drawTo(sf::RenderWindow& window) {
    window.draw(player);
}

void Player::move(sf::Vector2f distance) {
    player.move(distance);
}

void Player::setPos(sf::Vector2f newPos) {
    player.setPosition(newPos);
}

int Player::getX() {
	return player.getPosition().x;
}

int Player::getY() {
    return player.getPosition().y;
}

void Player::inputProcessing() {

	//JUMP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		move({ 0, -moveSpeed });
		isJumping = true;
	}
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		move({ moveSpeed, 0 });
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (getX() > moveSpeed)
			move({ -moveSpeed, 0 });
	}
}