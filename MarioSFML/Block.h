#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

/* --------------- BLOCK --------------- */

class Block
{
protected:
	sf::RectangleShape block;
public:
	Block(sf::Vector2f size, sf::Texture *texture);
	~Block() = default;
	virtual void collision() = 0;
	virtual void setPos(sf::Vector2f pos) = 0;
	virtual void drawTo(sf::RenderWindow& window) = 0;
};

/* --------------- GROUND --------------- */

class Ground : public Block
{
public:
	Ground(sf::Vector2f size, sf::Texture* texture);
	~Ground() = default;
	void collision();
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
};

/* --------------- BRICK --------------- */

class Brick : public Block
{
public:
	Brick(sf::Vector2f size, sf::Texture* texture);
	~Brick() = default;
	void collision();
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
};

#endif // !BLOCK_H