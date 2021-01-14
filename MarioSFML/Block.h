#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

/* --------------- BLOCK --------------- */

class Block
{
public:
	Block(sf::Vector2f size, sf::Texture *texture);
	~Block() = default;
	int getX();
	int getY();
	sf::FloatRect getGlobalBounds();
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
protected:
	sf::RectangleShape block;
};

/* --------------- GROUND --------------- */

class Ground : public Block
{
public:
	Ground(sf::Vector2f size, sf::Texture* texture);
	~Ground() = default;
};

/* --------------- BRICK --------------- */

class Brick : public Block
{
public:
	Brick(sf::Vector2f size, sf::Texture* texture);
	~Brick() = default;
};

#endif // !BLOCK_H