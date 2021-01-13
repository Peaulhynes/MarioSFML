#ifndef GROUND_H
#define GROUND_H

#include "Block.h"

class Ground : public Block
{
public:
	Ground(sf::Vector2f size, sf::Texture* texture);
	~Ground() = default;
	void collision();
	void setPos(sf::Vector2f pos);
	void drawTo(sf::RenderWindow & window);
};

#endif // !GROUND_H


