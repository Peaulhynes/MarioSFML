#include "Map.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>


Map::Map(AssetsManager& assets, sf::RenderWindow& window) {

	int groundLayers = 3;
	int blockPerLine = 60;

	this->gravity = 9.81f;
	this->blockSize = 40;
	this->size = sf::Vector2f{ blockPerLine * blockSize, (float)window.getSize().y };

	float groundY = size.y - groundLayers * blockSize;

	this->background.setTexture(assets.getTRef("background"));
	readMap(assets);

	//Quadtree quadtree(window.getView().getCenter().x, window.getView().getCenter().y, window.getSize().x / 2);
	Quadtree quadtree(6000/2, 1600/2, 6000/2);
	this->quadtree.setXYHalf(quadtree.getX(),quadtree.getY(),quadtree.getHalf());
	//std::cout << this->quadtree.getX() << "\n";

	readMap(assets, this->quadtree);

	//this->player = new Player({ 40, 40 }, &assets.getTRef("player"), { 50, groundY });

	/*for (int i = 0; i < groundLayers; i++) {
		for (int j = 0; j < blockPerLine; j++) {
			Ground* ground = new Ground({ blockSize, blockSize }, &assets.getTRef("ground"), { blockSize * j, size.y - blockSize * i });
			groundVector.push_back(ground);
		}
	}*/

	/*Gomba* enemy1 = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { 300, groundY });
	Gomba* enemy2 = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { 500, groundY });
	Gomba* enemy3 = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { 700, groundY });
	enemyVector.push_back(enemy1);
	enemyVector.push_back(enemy2);
	enemyVector.push_back(enemy3);*/

	//COINS
	/*
	std::vector<Coin*> coinVector;
	Coin coin1({ BLOCK_SIZE, BLOCK_SIZE }, &cointexture);
	Coin coin2({ BLOCK_SIZE, BLOCK_SIZE }, &cointexture);
	Coin coin3({ BLOCK_SIZE, BLOCK_SIZE }, &cointexture);
	coinVector.push_back(&coin1);
	coinVector.push_back(&coin2);
	coinVector.push_back(&coin3);
	coin1.setPos({ 200, 520 });
	coin2.setPos({ 120, 520 });
	coin3.setPos({ 400, 400 });
	*/
}

Map::~Map() {

	delete player;

	for (unsigned int i = 0; i < groundVector.size(); i++) {
		delete groundVector[i];
	}

	for (unsigned int i = 0; i < enemyVector.size(); i++) {
		delete enemyVector[i];
	}
}

void Map::draw(sf::RenderWindow& window) {
	window.draw(this->background);
	this->player->draw(window);

	for (unsigned int i = 0; i < groundVector.size(); i++) {
		groundVector[i]->draw(window);
	}
	for (unsigned int i = 0; i < enemyVector.size(); i++) {
		enemyVector[i]->draw(window);
	}

	for (unsigned int i = 0; i < coinVector.size(); i++) {
		coinVector[i]->draw(window);
	}

}

void Map::readMap(AssetsManager& assets, Quadtree& quadtree) {

	int row = 0, col = -1;
	char ch;
	std::fstream mapFile("assets/maps/map1.txt", std::fstream::in);
	std::string line;

	while (std::getline(mapFile, line)) {
		row++;
	}

	mapFile.clear();
	mapFile.seekg(0);

	int total = 0;
	
	while (mapFile >> std::noskipws >> ch) {
		if (ch == '\n') {
			row--;
			col = -1;
		}
		else {
			col++;
		}

		if (ch == 'P') {
			this->player = new Player({ 40, 40 }, &assets.getTRef("player"), { blockSize * col, size.y - row * blockSize});
		}

		if (ch == 'G') {
			Ground* ground = new Ground({ blockSize, blockSize }, &assets.getTRef("ground"), { blockSize * col, size.y - row * blockSize });
			groundVector.push_back(ground);
			quadtree.insert(blockSize * col, size.y - row * blockSize);
			std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() > 0)
				total++;
		}

		if (ch == '1') {
			Gomba* enemy = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { blockSize * col, size.y - row * blockSize });
			enemyVector.push_back(enemy);
			std::cout << blockSize * col << " X " << size.y - row * blockSize << " Y \n";
			quadtree.insert(blockSize * col, size.y - row * blockSize);
			std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);//regarder les valeurs surtout half
			std::vector<float> temp = std::get<0>(res);
			if(temp.size() > 0)
				total++;
			//std::vector<float> pointsX = quadtree.getPointsX();
			//std::cout << pointsX.size() << "\n";
			//std::cout << quadtree.getX() << " X \n";
		}

		if (ch == 'o') {
			Coin* coin = new Coin({ blockSize, blockSize }, &assets.getTRef("coin"), { blockSize * col, size.y - row * blockSize });
			coinVector.push_back(coin); 
			quadtree.insert(blockSize * col, size.y - row * blockSize);
			std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() > 0)
				total++;
		}
	}

	std::cout << total << std::endl; // 168 correspond bien � tous les �l�ments de la map (sans 2 ni P ni * car pas encore mis)
}

void Map::checkCollisions(int input) {
	
	//std::cout << player->getX() + player->getGlobalBounds().width / 2 << " x " << player->getY() + player->getGlobalBounds().height / 2 << " y " << player->getGlobalBounds().width << " half \n";
	//std::tuple <std::vector<float>, std::vector<float>> res = this->quadtree.queryRange(player->getX() + player->getGlobalBounds().width / 2, player->getY() + player->getGlobalBounds().height / 2, player->getGlobalBounds().width/2);
	/*std::tuple <std::vector<float>, std::vector<float>> res = this->quadtree.queryRange(920, 520, 200);
	std::vector<float> temp = std::get<0>(res);
	if (temp.size() > 0) {
		std::cout << temp.size() << "\n";
		float xTemp = temp[0];
		temp = std::get<1>(res);
		float yTemp = temp[0];
		if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp - (blockSize / 2), yTemp - (blockSize / 2), blockSize/2, blockSize/2))) {
			std::cout << "true \n";
		}
		else {
			std::cout << "false \n";
		}
	}*/

	/*std::tuple <std::vector<float>, std::vector<float>> collisions;
	collisions = quadtree.queryRange(enemyVector[0]->getGlobalBounds().left + (enemyVector[0]->getGlobalBounds().width / 2), enemyVector[0]->getGlobalBounds().top + (enemyVector[0]->getGlobalBounds().height / 2), enemyVector[0]->getGlobalBounds().width / 2);
	
	std::vector<float> temp = std::get<0>(collisions);
	std::cout << temp.size() << "\n";*/

	/*sf::FloatRect object;
	if (this->player->getGlobalBounds().intersects(object)) {
		std::cout << this->player->getGlobalBounds().intersects(object);
	}*/

	// collisions basiques
	/*for (int i = 0; i < enemyVector.size(); i++) {
		if (this->player->isCollidingWithEnemy(enemyVector[i])) {
			std::cout << "aie";
			if (input == 1) {
				player->setPosition(sf::Vector2f{ (float)enemyVector[i]->getGlobalBounds().left - player->getGlobalBounds().width, (float)player->getY() });
			}
			if (input == -1) {
				player->setPosition(sf::Vector2f{ (float)enemyVector[i]->getGlobalBounds().left + enemyVector[i]->getGlobalBounds().width, (float)player->getY() });
			}
			if (input == -2) {
				std::cout << "dead";
			}
		}
		
	}

	for (int i = 0; i < coinVector.size(); i++) {
		if (this->player->isCollidingWithCoin(coinVector[i])) {
			std::cout << "score";
		}
	}*/
	
	//fait ramer le jeu
	//for (int i = 0; i < groundVector.size(); i++) {
	//	if (this->player->collidesWithGround(groundVector[i])) {
	//		//std::cout << "ground";
	//		if (input == -2) {
	//			//player->setPosition(sf::Vector2f{ (float)player->getX(),(float)groundVector[i]->getGlobalBounds().top - player->getGlobalBounds().height });
	//			if (input == 1) {
	//				//player->setPosition(sf::Vector2f{ (float)groundVector[i]->getGlobalBounds().left - player->getGlobalBounds().width, (float)player->getY() });
	//			}
	//		}
	//		if (input == 1) {
	//			//player->setPosition(sf::Vector2f{ (float)groundVector[i]->getGlobalBounds().left - player->getGlobalBounds().width, (float)player->getY() });
	//			player->setPosition(sf::Vector2f{ (float)player->getX(),(float)groundVector[i]->getGlobalBounds().top - player->getGlobalBounds().height });
	//		}
	//		if (input == -1) {
	//			//player->setPosition(sf::Vector2f{ (float)groundVector[i]->getGlobalBounds().left + groundVector[i]->getGlobalBounds().width, (float)player->getY() });
	//		}
	//		
	//	}
	//}
}
