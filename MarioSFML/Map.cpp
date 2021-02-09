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

void Map::readMap(AssetsManager& assets) {

	int row = 0, col = -1;
	char ch;
	std::fstream mapFile("assets/maps/map1.txt", std::fstream::in);
	std::string line;

	while (std::getline(mapFile, line)) {
		row++;
	}

	mapFile.clear();
	mapFile.seekg(0);

	while (mapFile >> std::noskipws >> ch) {
		if (ch == '\n') {
			row--;
			col = -1;
		}
		else {
			col++;
		}

		if (ch == 'P') {
			this->player = new Player({ 40, 40 }, &assets.getTRef("player"), { blockSize * col, size.y - row * blockSize });
		}

		if (ch == 'G') {
			Ground* ground = new Ground({ blockSize, blockSize }, &assets.getTRef("ground"), { blockSize * col, size.y - row * blockSize });
			groundVector.push_back(ground);
		}

		if (ch == '1') {
			Gomba* enemy = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { blockSize * col, size.y - row * blockSize });
			enemyVector.push_back(enemy);
		}

		if (ch == 'o') {
			Coin* coin = new Coin({ blockSize, blockSize }, &assets.getTRef("coin"), { blockSize * col, size.y - row * blockSize });
			coinVector.push_back(coin);
		}
	}
}