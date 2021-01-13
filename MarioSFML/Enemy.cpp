#include "Enemy.h"

/* --------------- ENEMY --------------- */

Enemy::Enemy(sf::Vector2f size, sf::Texture* texture) {
    enemy.setSize(size);
    enemy.setTexture(texture);
}

/* --------------- GOMBA --------------- */

Gomba::Gomba(sf::Vector2f size, sf::Texture* texture) : Enemy(size, texture) {
    this->moveSpeed = 5;
}

void Gomba::collision() {
}

void Gomba::move(sf::Vector2f distance) {
    enemy.move(distance);
}

void Gomba::setPos(sf::Vector2f pos) {
    enemy.setPosition(pos);
}

void Gomba::drawTo(sf::RenderWindow& window) {
    window.draw(enemy);
}