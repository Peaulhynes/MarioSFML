#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Directions.h"

class Player
{
public:
	Player(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Player() = default;

    /* Draw player on specified window. */
	void draw(sf::RenderWindow& window);

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
    int getLife();
	sf::FloatRect getGlobalBounds();

    /* Process user input in game. */
    int inputProcessing(float deltaTime, float mapSizeX);

    /* Cause damage to player. */
    void damage();

    /* End player jumping. */
    void stopJumping();
    void setPosY(float posY);
    void setStartJumping();
    void setBaseY();

private:
    sf::RectangleShape player;
    float size;
    float moveSpeed;
    bool isJumping;
    float maxJump;
    float posY;
    float basePosY;
    bool startJumping;
    float gravity;
    int score;
    int life;
};

#endif