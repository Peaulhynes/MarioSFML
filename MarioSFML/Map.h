#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include "Enemy.h"
#include "Block.h"
#include "Player.h"
#include "Quadtree.h"

class Map
{
public:
	Player *player;
	std::map<std::pair<float, float>, Ground*> groundMap;
	std::map<std::pair<float, float>, Enemy*> enemyMap;
	std::map<std::pair<float, float>, Coin*> coinMap;

	Quadtree quadtree;

	float gravity;
	float blockSize;
	sf::Vector2f size;
	sf::Vector2i nbBlocks;


public:
	Map(AssetsManager& assets, sf::RenderWindow& window);
	~Map();

	/* Draw map on specified window. */
	void draw(sf::RenderWindow& window);

	/* Load map from text file and initialize it in memory. */
	void readMap(AssetsManager& assets, Quadtree& quadtree);

	/* Check collisions in map. */
	void checkCollisions(int input);
};

#endif // !MAP_H