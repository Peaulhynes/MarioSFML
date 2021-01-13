#include "Map.h"
#include "ErrorCodes.h"
#include <iostream>

Map::Map() {

	//NE FONCTIONNE PAS : texture détruite à la fin de la fonction
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/sprites/background.png", sf::IntRect(0, 0, 1200, 800))) {
		std::cout << "[ERROR] Load background texture failed." << std::endl;
		exit(LoadingCodes::BACKGROUND_CODE);
	}
	this->background.setTexture(backgroundTexture);




	/* ANCIEN CODE : dans l'idéal, reproduire tout ça dans une classe map
	
	//GROUND
	sf::Texture groundTexture;
	if (!groundTexture.loadFromFile("assets/sprites/ground.png")) {
		exit(LoadingCodes::GROUND_CODE);
	}
	std::vector<Ground*> groundVector;
	for (int i = 0; i < groundLayers; i++) {
		for (int j = 0; j < blockPerLine; j++) {
			Ground* dirt = new Ground({ blockSize, blockSize }, &groundTexture);
			groundVector.push_back(dirt);
			dirt->setPos({ blockSize * j, windowHeight - blockSize * i });
		}
	}

	//ENEMIES
	sf::Texture gombaTexture;
	if (!gombaTexture.loadFromFile("assets/sprites/gomba.png")) {
		exit(LoadingCodes::GOMBA_CODE);
	}

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
	sf::Texture cointexture;
	if (!cointexture.loadFromFile("assets/sprites/coin.png")) {
		exit(LoadingCodes::COIN_CODE);
	}
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

void Map::drawTo(sf::RenderWindow& window) {
	window.draw(this->background);
}