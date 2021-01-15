#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

/* --------------- ENEMY --------------- */

class Enemy
{
public:
	Enemy(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Enemy() = default;
	sf::FloatRect getGlobalBounds();
	void move(sf::Vector2f distance);
	void setPosition(sf::Vector2f position);
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape enemy;
	float moveSpeed;
};

/* --------------- GOMBA --------------- */

class Gomba : public Enemy
{
public:
	Gomba(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Gomba() = default;
};

#endif // !ENEMY_H