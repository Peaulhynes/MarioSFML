#include "Enemy.h"

/* --------------- ENEMY --------------- */

Enemy::Enemy(sf::Vector2f size, sf::Texture* texture) {
    enemy.setSize(size);
    enemy.setTexture(texture);
    moveSpeed = 0;
}

sf::FloatRect Enemy::getGlobalBounds() {
    return enemy.getGlobalBounds();
}

void Enemy::move(sf::Vector2f distance) {
    enemy.move(distance);
}

void Enemy::setPos(sf::Vector2f pos) {
    enemy.setPosition(pos);
}

void Enemy::drawTo(sf::RenderWindow& window) {
    window.draw(enemy);
}

/* --------------- GOMBA --------------- */

Gomba::Gomba(sf::Vector2f size, sf::Texture* texture) : Enemy(size, texture) {
    moveSpeed = 5;
}

