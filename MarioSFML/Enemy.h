#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

/* --------------- ENEMY --------------- */

class Enemy
{
public:
	Enemy(sf::Vector2f size, sf::Texture* texture);
	~Enemy() = default;
	sf::FloatRect getGlobalBounds();
	void move(sf::Vector2f distance);
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape enemy;
	float moveSpeed;
};

/* --------------- GOMBA --------------- */

class Gomba : public Enemy
{
public:
	Gomba(sf::Vector2f size, sf::Texture* texture);
	~Gomba() = default;
};

#endif // !ENEMY_H