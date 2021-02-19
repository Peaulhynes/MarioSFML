#include "Player.h"

Player::Player(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position) {
    player.setSize(size);
    player.setTexture(texture);
	player.setPosition(position);
	this->size = size.y;
	this->moveSpeed = 200.f;
	this->isJumping = false;
	this->maxJump = 200.f;
	this->posY = getY();
	this->basePosY = getY();
	this->startJumping = false;
	this->gravity = 2.f;
	this->score = 0;
	this->life = 3;

}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
}

void Player::jump(sf::Vector2f distance) {

	//up
	if (isJumping && getY() > posY - maxJump) {
		player.move(distance * gravity);
	}
	//need to go down because maxJump reached
	if (isJumping && getY() <= posY - maxJump) {
		isJumping = false;
	}
	//down
	if (!isJumping && getY() < posY) {
		player.move(distance * -gravity);
		//put the player on the ground (without it the player is a bit in the ground)
		if (getY() > posY) {
			setPosition({ (float)getX(),posY });
		}
	}
	//allow jump
	if (!isJumping && getY() == posY) {
		startJumping = false;
		posY = basePosY;
	}
}

void Player::setPosition(sf::Vector2f position) {
    player.setPosition(position);
}

void Player::setScore(int score) {
	this->score = score;
}

float Player::getX() {
	return player.getPosition().x;
}

float Player::getY() {
	return player.getPosition().y;
}

float Player::getSpeed() {
	return moveSpeed;
}

int Player::getScore() {
	return score;
}

int Player::getLife() {
	return this->life;
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}

void Player::damage() {
	this->life = std::max(this->life - 1, 0);
}

int Player::inputProcessing(float deltaTime, float mapSizeX) {

	//JUMP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		if (!startJumping) {
			posY = getY(); 
			isJumping = true;
			startJumping = true;
		}
		
		jump({ 0, -moveSpeed * deltaTime });
		
		//RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (getX() + (moveSpeed * deltaTime) < mapSizeX)
				player.move({ moveSpeed * deltaTime, 0 });
		}
		//LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if(getX() + (-moveSpeed * deltaTime) > 0)
				player.move({ -moveSpeed * deltaTime, 0 });
		}

		return Direction::UP;
	}
	else {
		isJumping = false;
		jump({ 0, -moveSpeed * deltaTime });
	}

	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (getX() + (moveSpeed * deltaTime) < mapSizeX)
			player.move({ moveSpeed * deltaTime, 0 });
		return Direction::RIGHT;
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (getX() + (-moveSpeed * deltaTime) > 0)
			if (getX() > moveSpeed * deltaTime)
				player.move({ -moveSpeed * deltaTime, 0 });
		return Direction::LEFT;
	}

	return Direction::DOWN;
}

void Player::stopJumping() {
	isJumping = false;
}

void Player::setPosY(float posY) {
	this->posY = posY;
}

void Player::setStartJumping() {
	this->startJumping = false;
}

void Player::setBaseY() {
	this->posY = basePosY;;
}