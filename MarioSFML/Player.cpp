#include "Player.h"

Player::Player(sf::Vector2f size, sf::Texture* texture) {
    player.setSize(size);
    player.setTexture(texture);
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

int Player::getY() {
    return player.getPosition().y;
}