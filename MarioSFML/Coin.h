#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

class Coin 
{
public:
    Coin(sf::Vector2f size, sf::Texture* texture);
    sf::FloatRect getGlobalBounds();
    void setPos(sf::Vector2f newPos);
    void drawTo(sf::RenderWindow& window);
private:
    sf::RectangleShape coin;
};

#endif // !COIN_H

