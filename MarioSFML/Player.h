#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Block.h"

class Player
{
public:
	Player(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Player() = default;

    /* Draw player on specified window. */
	void draw(sf::RenderWindow& window);

    /* Move player with specified distance. */
	void move(sf::Vector2f distance);

    /* Make the player jump with specified distance. */
	void jump(sf::Vector2f distance);

    /* Set player position. */
	void setPosition(sf::Vector2f position);

    /* Set player score. */
    void setScore(int score);

    /* Get player X coordinates. */
	float getX();

    /* Get player Y coordinates. */
	float getY();

    /* Get player speed. */
    float getSpeed();

    /* Get player score. */
    int getScore();

    /* Get player collision box. */
	sf::FloatRect getGlobalBounds();

    /* Process user input in game. */
    int inputProcessing(float deltaTime);

    /* Cause damage to player. */
    void damage();

    /* End player jumping. */
    void stopJumping();

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