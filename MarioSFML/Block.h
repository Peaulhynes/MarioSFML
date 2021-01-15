#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

/* --------------- BLOCK --------------- */

class Block
{
public:
	Block(sf::Vector2f size, sf::Texture *texture, sf::Vector2f position);
	~Block() = default;
	int getX();
	int getY();
	sf::FloatRect getGlobalBounds();
	void setPosition(sf::Vector2f position);
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

/* --------------- BRICK --------------- */

class Brick : public Block
{
public:
	Brick(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Brick() = default;
};

/* --------------- COIN --------------- */

class Coin : public Block
{
public:
	Coin(sf::Vector2f size, sf::Texture* texture, sf::Vector2f position);
	~Coin() = default;
};

#endif // !BLOCK_H