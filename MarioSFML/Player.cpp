#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Texture* texture) {
    player.setSize(size);
    player.setTexture(texture);
	this->moveSpeed = 5.f;
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
		std::cout << "jump" << std::endl;
	}
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		move({ moveSpeed, 0 });
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		move({ -moveSpeed, 0 });
	}

}