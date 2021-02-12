#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) {
    player.setSize(size);
    player.setTexture(texture);
	player.setPosition(position);
	this->size = size.y;
	this->moveSpeed = 200.f;
	this->isJumping = false;
	this->maxJump = 200.f;
	this->posY = getY();
	this->startJumping = false;
	this->gravity = -1.5f;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
}

void Player::move(sf::Vector2f distance) {
    player.move(distance);
}

void Player::jump(sf::Vector2f distance) {

	if (isJumping && getY() > posY - maxJump) {
		player.move(distance * -gravity);
	}

	if (isJumping && getY() <= posY - maxJump) {
		isJumping = false;
	}
	
	if (!isJumping && getY() < posY) {
		player.move(distance * gravity);

		if (getY() > posY) {
			setPosition({ (float)getX(),posY });
		}
	}

	if (!isJumping && getY() == posY) {
		startJumping = false;
	}
}

void Player::setPosition(sf::Vector2f position) {
    player.setPosition(position);
}

float Player::getX() {
	return player.getPosition().x;
}

float Player::getY() {
	return player.getPosition().y;
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}

/*bool Player::isCollidingWithCoin(Coin* coin) {
	return player.getGlobalBounds().intersects(coin->getGlobalBounds());
}

bool Player::isCollidingWithEnemy(Enemy* enemy) {
	return player.getGlobalBounds().intersects(enemy->getGlobalBounds());
}

int Player::collidesWithGround(Ground* ground) {
	if (player.getGlobalBounds().intersects(ground->getGlobalBounds())) {
		if (getY() < ground->getY()) {
			return Directions::UP;
		}
		else if (getY() + size > ground->getY()) {
			return Directions::DOWN;
		}
	}
	else
		return -1;
}*/

int Player::inputProcessing(float deltaTime) {

	//float input;
	//JUMP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		if (!startJumping) {
			posY = getY();
			isJumping = true;
			startJumping = true;
		}
		
		jump({ 0, -moveSpeed * deltaTime });

		//input = 0;

		//RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move({ moveSpeed * deltaTime, 0 });
			//input = 2;
		}
		//LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if (getX() > moveSpeed * deltaTime)
				move({ -moveSpeed * deltaTime, 0 });
			//input = 3;
		}

		return 0;
	}
	else {
		isJumping = false;

		jump({ 0, -moveSpeed * deltaTime });

		
	}
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		move({ moveSpeed * deltaTime, 0 });
		return 1;
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (getX() > moveSpeed * deltaTime)
			move({ -moveSpeed * deltaTime, 0 });
		return -1;
	}

	return -2;
}