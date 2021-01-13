#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

class Coin {

private:
    sf::RectangleShape coin;

public:
    Coin(sf::Vector2f size, sf::Texture* texture);
    void drawTo(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();
    void setPos(sf::Vector2f newPos);
};

#endif // !COIN_H

