#ifndef BRICK_H
#define BRICK_H
#include "Block.h"

class Brick : public Block
{
public:
	Brick(sf::Vector2f size, sf::Texture* texture);
	~Brick() = default;
	void collision();
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	//sf::FloatRect getBounds();
};

#endif // !BRICK_H



