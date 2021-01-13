#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
class Player
{
private:
    sf::RectangleShape player;

public:
    Player(sf::Vector2f size, sf::Texture* texture);
    ~Player() = default;
    void drawTo(sf::RenderWindow& window);
    void move(sf::Vector2f distance);
    void setPos(sf::Vector2f newPos);
    int getY();
};

#endif