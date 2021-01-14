#include "Map.h"
#include "AssetsManager.h"
#include <iostream>

Map::Map(AssetsManager& assets, sf::RenderWindow& window) {

	int groundLayers = 3;
	int blockPerLine = 60;

	this->gravity = 9.81;
	this->blockSize = 40;
	this->size = sf::Vector2f{ blockPerLine * blockSize, (float)window.getSize().y };

	this->background.setTexture(assets.getTRef("background"));
	this->player = new Player({ 40, 40 }, &assets.getTRef("player"));
	player->setPosition({ 50 , size.y - groundLayers * blockSize });

	for (int i = 0; i < groundLayers; i++) {
		for (int j = 0; j < blockPerLine; j++) {
			Ground* ground = new Ground({ blockSize, blockSize }, &assets.getTRef("ground"));
			groundVector.push_back(ground);
			ground->setPosition({ blockSize * j, size.y - blockSize * i });
		}
	}

	/*
	//ENEMIES

	std::vector<Gomba*> gombaVector;
	Gomba enemy1({ BLOCK_SIZE, BLOCK_SIZE }, &gombaTexture);
	Gomba enemy2({ BLOCK_SIZE, BLOCK_SIZE }, &gombaTexture);
	Gomba enemy3({ BLOCK_SIZE, BLOCK_SIZE }, &gombaTexture);
	gombaVector.push_back(&enemy1);
	gombaVector.push_back(&enemy2);
	gombaVector.push_back(&enemy3);
	enemy1.setPos({ 300, 600 });
	enemy2.setPos({ 500, 600 });
	enemy3.setPos({ 700, 600 });

	//COINS
	
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
}

void Map::draw(sf::RenderWindow& window) {
	window.draw(this->background);
	this->player->draw(window);
	for (int i = 0; i < groundVector.size(); i++) {
		groundVector[i]->draw(window);
	}
	/*
	for (int i = 0; i < gombaVector.size(); i++) {
		gombaVector[i]->draw(window);
	}

	for (int i = 0; i < coinVector.size(); i++) {
		coinVector[i]->draw(window);
	}
	*/
}