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
	sf::Sprite background;
	Player *player;
	std::vector<Ground*> groundVector;
	std::vector<Enemy*> enemyVector;
	std::vector<Coin*> coinVector;

	Quadtree quadtree;

	float gravity;
	float blockSize;
	sf::Vector2f size;

public:
	Map(AssetsManager& assets, sf::RenderWindow& window);
	~Map();
	void draw(sf::RenderWindow& window);
	void readMap(AssetsManager& assets, Quadtree& quadtree);
	void checkCollisions(int input);
};

#endif // !MAP_H