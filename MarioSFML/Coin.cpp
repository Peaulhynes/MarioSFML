#include "Coin.h"

Coin::Coin(sf::Vector2f size, sf::Texture *texture) {
    coin.setSize(size);
    coin.setTexture(texture);
}

void Coin::draw(sf::RenderWindow& window) {
    window.draw(coin);
}

sf::FloatRect Coin::getGlobalBounds() {
    return coin.getGlobalBounds();
}

void Coin::setPosition(sf::Vector2f newPos) {
    coin.setPosition(newPos);
}