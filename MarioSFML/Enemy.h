#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

/* --------------- ENEMY --------------- */

class Enemy
{
protected:
	sf::RectangleShape enemy;
public:
	Enemy(sf::Vector2f size, sf::Texture* texture);
	~Enemy() = default;
	virtual void collision() = 0;
	virtual void move(sf::Vector2f distance) = 0;
	virtual void setPos(sf::Vector2f pos) = 0;
	virtual void drawTo(sf::RenderWindow& window) = 0;
};

/* --------------- GOMBA --------------- */

class Gomba : public Enemy
{
private:
	float moveSpeed;
public:
	Gomba(sf::Vector2f size, sf::Texture* texture);
	~Gomba() = default;
	void collision();
	void move(sf::Vector2f distance);
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
};

#endif // !ENEMY_H