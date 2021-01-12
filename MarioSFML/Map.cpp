#include "Map.h"
#include "ErrorCodes.h"
#include <iostream>

Map::Map() {

	//FONCTIONNE PAS : texture détruite à la fin de la fonction
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/sprites/background.png", sf::IntRect(0, 0, 1200, 800))) {
		std::cout << "[ERROR] Load background texture failed." << std::endl;
		exit(LoadingCodes::BACKGROUND_CODE);
	}
	this->background.setTexture(backgroundTexture);

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
}

void Map::drawTo(sf::RenderWindow& window) {
	window.draw(this->background);
}