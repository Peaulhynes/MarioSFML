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
	std::map<std::pair<float, float>, Flag*> flagMap;

	Quadtree* quadtree;

	float blockSize;
	sf::Vector2f size;
	sf::Vector2i nbBlocks;

	bool active;
public:
	Map(AssetsManager& assets, sf::RenderWindow& window);
	~Map();

	/* Draw map on specified window. */
	void draw(sf::RenderWindow& window);

	/* Load map from text file and initialize it in memory. */
	void readMap(AssetsManager& assets, std::string& filename);

	/* Check collisions in map. */
	int checkCollisions(int input);
};

#endif // !MAP_H