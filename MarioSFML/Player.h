#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Coin.h"
#include "Enemy.h"
#include "Block.h"
#include "Directions.h"

class Player
{
public:
    Player(sf::Vector2f size, sf::Texture* texture);
    ~Player() = default;
    void drawTo(sf::RenderWindow& window);
    void move(sf::Vector2f distance);
    void setPos(sf::Vector2f newPos);
    int getX();
    int getY();
    sf::FloatRect getGlobalBounds();
    bool isCollidingWithCoin(Coin* coin);
    bool isCollidingWithEnemy(Enemy* enemy);
    int collidesWithGround(Ground* ground);
    void inputProcessing();
private:
    sf::RectangleShape player;
    float size;
    float moveSpeed;
    bool isJumping;
};

#endif