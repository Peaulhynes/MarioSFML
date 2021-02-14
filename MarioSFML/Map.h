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
	/*std::vector<Ground*> groundVector;
	std::vector<Enemy*> enemyVector;
	std::vector<Coin*> coinVector;*/
	std::map<std::pair<float, float>, Ground*> groundMap;
	std::map<std::pair<float, float>, Enemy*> enemyMap;
	std::map<std::pair<float, float>, Coin*> coinMap;

	Quadtree quadtree;

	float gravity;
	float blockSize;
	sf::Vector2f size;
	sf::Vector2f nbBlocks;


public:
	Map(AssetsManager& assets, sf::RenderWindow& window);
	~Map();
	void draw(sf::RenderWindow& window);
	void readMap(AssetsManager& assets, Quadtree& quadtree);
	void checkCollisions(int input);
};

#endif // !MAP_H