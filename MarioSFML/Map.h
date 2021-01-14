#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Coin.h"
#include "Enemy.h"
#include "Block.h"
#include "Player.h"

class Map
{
private:
	sf::Sprite background;
	//Player* player;
	float gravity;
public:
	Map();
	~Map();
	void drawTo(sf::RenderWindow& window);
};

#endif // !MAP_H