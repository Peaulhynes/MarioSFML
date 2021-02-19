#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

/* --------------- BLOCK --------------- */

class Block
{
public:
	Block(sf::Vector2f size, sf::Texture *texture, sf::Vector2f position);
	~Block() = default;

	/* Get block X coordinates. */
	float getX();

	/* Get block Y coordinates. */
	float getY();

	/* Get block collision box. */
	sf::FloatRect getGlobalBounds();

	/* Set block position. */
	void setPosition(sf::Vector2f position);

	/* Draw block on specified window. */
	void draw(sf::RenderWindow& window);

protected:
	sf::RectangleShape block;
};

/* --------------- GROUND --------------- */

class Ground : public Block
{
public:
	Ground(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Ground() = default;
};

/* --------------- COIN --------------- */

class Coin : public Block
{
public:
	Coin(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Coin() = default;
};

/* --------------- FLAG --------------- */

class Flag : public Block
{
public:

	Flag(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Flag() = default;
};

#endif // !BLOCK_H