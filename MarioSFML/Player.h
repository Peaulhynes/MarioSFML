#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Block.h"
#include "Directions.h"

class Player
{
public:
	Player(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Player() = default;
	void draw(sf::RenderWindow& window);
	void move(sf::Vector2f distance);
	void jump(sf::Vector2f distance);
	void setPosition(sf::Vector2f position);
    void setScore(int score);
	float getX();
	float getY();
    int getScore();
	sf::FloatRect getGlobalBounds();
   /* bool isCollidingWithCoin(Coin* coin);
    bool isCollidingWithEnemy(Enemy* enemy);
    int collidesWithGround(Ground* ground);*/
    int inputProcessing(float deltaTime);
    void getDamage();
    void stopJumping();
    //void setPosY(float posY);

private:
    sf::RectangleShape player;
    float size;
    float moveSpeed;
    bool isJumping;
    float maxJump;
    float posY;
    bool startJumping;
    float gravity;
    int score;
    int life;
};

#endif