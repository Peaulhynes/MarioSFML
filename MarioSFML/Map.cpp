#include "Map.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

#define BLOCKSIZE 40;
#define QUADTREE_X 3000
#define QUADTREE_Y 800

Map::Map(AssetsManager& assets, sf::RenderWindow& window) {

	this->blockSize = BLOCKSIZE;
	this->size = {(float)window.getSize().x, (float)window.getSize().y };

	this->quadtree = new Quadtree(QUADTREE_X , QUADTREE_Y , QUADTREE_X , QUADTREE_Y );

	readMap(assets);

	this->size = { nbBlocks.x * blockSize, nbBlocks.y * blockSize };
}

Map::~Map() {

	delete player;
	player = nullptr;

	groundMap.clear();
	enemyMap.clear();
	coinMap.clear();
	flagMap.clear();

	delete quadtree;
	quadtree = nullptr;
}

void Map::draw(sf::RenderWindow& window) {

	this->player->draw(window);

	for (auto it = groundMap.begin(); it != groundMap.end(); ++it) {
		it->second->draw(window);
	}

	for (auto it = enemyMap.begin(); it != enemyMap.end(); ++it) {
		it->second->draw(window);
	}

	for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
		it->second->draw(window);
	}

	for (auto it = flagMap.begin(); it != flagMap.end(); ++it) {
		it->second->draw(window);
	}

}

void Map::readMap(AssetsManager& assets) {

	int row = 0, col = -1;
	int maxCol = 0;
	char ch;
	std::fstream mapFile("assets/maps/map1.txt", std::fstream::in);
	std::string line;

	while (std::getline(mapFile, line)) {
		row++;
	}

	mapFile.clear();
	mapFile.seekg(0);

	this->nbBlocks.y = row;

	/* Read each char from the file */
	while (mapFile >> std::noskipws >> ch) {
		if (ch == '\n') {
			row--;
			if (col > maxCol)
				maxCol = col;
			col = -1;
		}
		else {
			col++;
		}

		if (ch == 'P') {
			this->player = new Player({ blockSize, blockSize }, &assets.getTRef("player"), { blockSize * col, size.y - row * blockSize});
		}

		if (ch == 'G') {
			Ground* ground = new Ground({ blockSize, blockSize }, &assets.getTRef("ground"), { blockSize * col, size.y - row * blockSize });
			groundMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),ground });
			quadtree->insert(blockSize * col, size.y - row * blockSize,"ground");
		}

		if (ch == '1') {
			Wolf* enemy = new Wolf({ blockSize, blockSize }, &assets.getTRef("wolf"), { blockSize * col, size.y - row * blockSize });
			enemyMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),enemy });
			quadtree->insert(blockSize * col, size.y - row * blockSize, "enemy");
		}

		if (ch == 'o') {
			Coin* coin = new Coin({ blockSize, blockSize }, &assets.getTRef("coin"), { blockSize * col, size.y - row * blockSize });
			coinMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),coin });
			quadtree->insert(blockSize * col, size.y - row * blockSize,"coin");
		}

		if (ch == '*') {
			Flag* flag = new Flag({ blockSize, blockSize }, &assets.getTRef("flagMiddle"), { blockSize * col, size.y - row * blockSize });
			flagMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),flag });
			quadtree->insert(blockSize * col, size.y - row * blockSize, "flag");
		}

		if (ch == '=') {
			Flag* flag = new Flag({ blockSize, blockSize }, &assets.getTRef("flagBottom"), { blockSize * col, size.y - row * blockSize });
			flagMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),flag });
			quadtree->insert(blockSize * col, size.y - row * blockSize, "flag");
		}

		if (ch == '-') {
			Flag* flag = new Flag({ blockSize, blockSize }, &assets.getTRef("flagTop"), { blockSize * col, size.y - row * blockSize });
			flagMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),flag });
			quadtree->insert(blockSize * col, size.y - row * blockSize, "flag");
		}
	}
	this->nbBlocks.x = maxCol + 1;
}

int Map::checkCollisions(int input) {

	// player goes right
	if (input == Direction::RIGHT) {
		/* check if the player is colliding at his position */
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX() + (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);

		/* if the player is colliding */
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];

			/* if the player is colliding with an enemy */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type =="enemy") {
				player->damage();
				player->setPosition(sf::Vector2f{ xTemp - player->getGlobalBounds().width, player->getY() });
				if (player->getLife() == 0)
					return GameStatus::GAMEOVER;
			}

			/* if the player is colliding with a coin */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize)) && type == "coin") {
				//remove coin from quadtree
				this->quadtree->removeItem(player->getX() + (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				//remove coin from vector
				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize ) {
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}
				
				this->player->setScore(this->player->getScore() + 1);
			}

			/* if the player is colliding with a ground */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {

				player->setPosition(sf::Vector2f{ xTemp - player->getGlobalBounds().width + 16 , player->getY() - 1 });
				player->setPosY(player->getY() -1);
				player->setStartJumping();
			}

			/* if the player is colliding with a flag */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type == "flag") {
				return GameStatus::VICTORY;
			}
		}
		/* check if the player is colliding at his position with the ground  (add +1 to height, necessary to do this otherwise bug when the player goes left and right */
		else {
			std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX() + (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2) + 1, player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() == 0) {
				player->setBaseY();
				player->setStartJumping();
			}
		}
	}

	//player goes left
	if (input == Direction::LEFT) {
		/* check if the player is colliding at his position */
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX() - (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);

		/* if the player is colliding */
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];

			/* if the player is colliding with an enemy */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "enemy") {
				player->damage();
				player->setPosition(sf::Vector2f{ xTemp + player->getGlobalBounds().width , player->getY() });
				if (player->getLife() == 0)
					return GameStatus::GAMEOVER;
			}

			/* if the player is colliding with a coin */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "coin") {
				//remove coin from quadtree
				this->quadtree->removeItem(player->getX() - (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				//remove coin from vector
				for(auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize  && it->first.second <= yTemp + blockSize ) {
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}

			/* if the player is colliding with a ground */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				player->setPosition(sf::Vector2f{ xTemp + blockSize - 16 , player->getY() - 1});
				player->setPosY(player->getY() - 1);
				player->setStartJumping();
			}

			/* if the player is colliding with a flag */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type == "flag") {
				return GameStatus::VICTORY;
			}
		}
		/* check if the player is colliding at his position with the ground  (add +1 to height, necessary to do this otherwise bug when the player goes left and right */
		else {
			std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX() - (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2) + 1, player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() == 0) {
				player->setBaseY();
				player->setStartJumping();
			}
		}
	}

	// player fall
	if (input == Direction::DOWN) {
		/* check if the player is colliding at his position */
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);

		/* if the player is colliding */
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];

			/* if the player is colliding with an enemy */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize )) && type == "enemy") {
				//remove enemy from quadtree
				this->quadtree->removeItem(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
				
				//remove enemy from vector
				for (auto it = enemyMap.begin(); it != enemyMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize) {
						enemyMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}
			}

			/* if the player is colliding with a coin */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "coin") {
				//remove coin from quadtree
				this->quadtree->removeItem(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				//remove coin from vector
				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize ) {
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}

			/* if the player is colliding with a ground */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				player->setPosition(sf::Vector2f{ player->getX() , yTemp - blockSize + 15 });
				player->setPosY(yTemp - blockSize + 14);
				player->setStartJumping();
			}

			/* if the player is colliding with a flag */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type == "flag") {
				return GameStatus::VICTORY;
			}
		}
	}

	// player jump
	if (input == Direction::UP) {
		/* check if the player is colliding at his position */
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree->queryRange(player->getX(), player->getY() - (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);

		/* if the player is colliding */
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];

			/* if the player is colliding with an enemy */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "enemy") {
				player->damage();
				player->stopJumping();
				if (player->getLife() == 0)
					return GameStatus::GAMEOVER;
			}

			/* if the player is colliding with a coin */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize)) && type == "coin") {
				//remove coin from quadtree
				this->quadtree->removeItem(player->getX(), player->getY() - (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				//remove coin from vector
				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize  && it->first.first <= xTemp + blockSize && it->first.second >= yTemp - blockSize  && it->first.second <= yTemp + blockSize ) {
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}
			
			/* if the player is colliding with a ground */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				player->stopJumping();
			}

			/* if the player is colliding with a flag */
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type == "flag") {
				return GameStatus::VICTORY;
			}
		}
	}

	return GameStatus::INGAME;

}
