#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include "Enemy.h"
#include "Block.h"
#include "Player.h"

class Map
{
public:
	sf::Sprite background;
	Player *player;
	std::vector<Ground*> groundVector;
	std::vector<Enemy*> enemyVector;
	std::vector<Coin*> coinVector;

	float gravity;
	float blockSize;
	sf::Vector2f size;

public:
	Map(AssetsManager& assets, sf::RenderWindow& window);
	~Map();
	void draw(sf::RenderWindow& window);
};

#endif // !MAP_H