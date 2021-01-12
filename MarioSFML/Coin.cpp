#include "Coin.h"

Coin::Coin(sf::Vector2f size, sf::Texture *texture) {
    coin.setSize(size);
    coin.setTexture(texture);
}

void Coin::drawTo(sf::RenderWindow& window) {
    window.draw(coin);
}

sf::FloatRect Coin::getGlobalBounds() {
    return coin.getGlobalBounds();
}

void Coin::setPos(sf::Vector2f newPos) {
    coin.setPosition(newPos);
}