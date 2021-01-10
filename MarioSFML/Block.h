#pragma once

#include <SFML/Graphics.hpp>

class Block
{
protected:
	sf::RectangleShape block;
public:
	Block(sf::Vector2f size, sf::Texture *texture);
	~Block();
	virtual void collision() = 0;
	virtual void setPos(sf::Vector2f pos) = 0;
	virtual void drawTo(sf::RenderWindow& window) = 0;
	//virtual sf::FloatRect getBounds() = 0;
};

