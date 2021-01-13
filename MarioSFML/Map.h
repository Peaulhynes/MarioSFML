#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Block.h"

class Map
{
public:
	sf::Sprite background;
public:
	Map();
	~Map();
	void drawTo(sf::RenderWindow& window);
};

#endif // !MAP_H