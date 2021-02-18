#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

/* --------------- ENEMY --------------- */

class Enemy
{
public:
	Enemy(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Enemy() = default;

	/* Get enemy collision box. */
	sf::FloatRect getGlobalBounds();

	/* Move enemy with specified distance. */
	void move(sf::Vector2f distance);

	/* Set enemy position. */
	void setPosition(sf::Vector2f position);

	/* Draw enemy on specified window. */
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape enemy;
	float moveSpeed;
};

/* --------------- WOLF --------------- */

class Wolf : public Enemy
{
public:
	Wolf(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Wolf() = default;
};

#endif // !ENEMY_H