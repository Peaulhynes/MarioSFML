#include "Map.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

#define BLOCKSIZE 64;

Map::Map(AssetsManager& assets, sf::RenderWindow& window) {

	/* A SUPPRIMER A LONG TERME*/
	int groundLayers = 3;
	int blockPerLine = 60;
	float groundY = size.y - groundLayers * blockSize;

	this->gravity = 9.81f;
	this->blockSize = BLOCKSIZE;
	this->size = {(float)window.getSize().x, (float)window.getSize().y };

	//Quadtree quadtree(window.getView().getCenter().x, window.getView().getCenter().y, window.getSize().x / 2);
	Quadtree quadtree(6000/2, 1600/2, 6000 / 2,1600/2);
	this->quadtree.setXYHalf(quadtree.getX(), quadtree.getY(), quadtree.getHalfX(), quadtree.getHalfY());
	//std::cout << this->quadtree.getX() << "\n";

	readMap(assets, this->quadtree);

	this->size = { nbBlocks.x * blockSize, nbBlocks.y * blockSize };
}

Map::~Map() {

	delete player;
	player = nullptr;

	groundMap.clear();
	enemyMap.clear();
	coinMap.clear();
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

}

void Map::readMap(AssetsManager& assets, Quadtree& quadtree) {

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

	int total = 0;
	this->nbBlocks.y = row;
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
			//groundVector.push_back(ground);
			groundMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),ground });
			quadtree.insert(blockSize * col, size.y - row * blockSize,"ground");
			/*std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() > 0)
				total++;*/
		}

		if (ch == '1') {
			Gomba* enemy = new Gomba({ blockSize, blockSize }, &assets.getTRef("gomba"), { blockSize * col, size.y - row * blockSize });
			//enemyVector.push_back(enemy);
			enemyMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),enemy });
			//std::cout << blockSize * col << " X " << size.y - row * blockSize << " Y " << (blockSize * col) / 2 << " half \n";
			quadtree.insert(blockSize * col, size.y - row * blockSize,"enemy");
			//std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);//regarder les valeurs surtout half
			//std::vector<float> temp = std::get<0>(res);
			//if(temp.size() > 0)
			//	total++;
			//std::vector<float> pointsX = quadtree.getPointsX();
			//std::cout << pointsX.size() << "\n";
			//std::cout << quadtree.getX() << " X \n";
		}

		if (ch == 'o') {
			Coin* coin = new Coin({ blockSize, blockSize }, &assets.getTRef("coin"), { blockSize * col, size.y - row * blockSize });
			//coinVector.push_back(coin); 
			coinMap.insert({ std::make_pair(blockSize * col, size.y - row * blockSize),coin });
			quadtree.insert(blockSize * col, size.y - row * blockSize,"coin");
			//std::cout << blockSize * col << " x " << size.y - row * blockSize << " y \n";
			/*std::tuple <std::vector<float>, std::vector<float>> res = quadtree.queryRange(blockSize * col, size.y - row * blockSize, (blockSize * col) / 2);
			std::vector<float> temp = std::get<0>(res);
			if (temp.size() > 0)
				total++;*/
		}
	}
	this->nbBlocks.x = maxCol;
	//std::cout << total << std::endl; // 168 correspond bien � tous les �l�ments de la map (sans 2 ni P ni * car pas encore mis)
}

void Map::checkCollisions(int input) {

	// player goes right
	if (input == 1) {
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree.queryRange(player->getX() + (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize)) && type =="enemy") {
				player->damage();
				player->setPosition(sf::Vector2f{ xTemp - player->getGlobalBounds().width, player->getY() });
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize)) && type == "coin") {
				//remove coin from quadtree and vector
				this->quadtree.removeItem(player->getX() + (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize ) {
						//std::cout << it->first.first << " x " << it->first.second << " y \n";
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}
				
				this->player->setScore(this->player->getScore() + 1);
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				//put the player position to top ground position?
				player->setPosition(sf::Vector2f{ player->getX() , yTemp - blockSize + 15 });
			}
			/*else {
				player->setPosY(2000);
			}*/
		}
	}

	//player goes left
	if (input == -1) {
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree.queryRange(player->getX() - (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "enemy") {
				player->damage();
				player->setPosition(sf::Vector2f{ xTemp + player->getGlobalBounds().width , player->getY() });
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "coin") {
				//remove coin from quadtree and vector
				this->quadtree.removeItem(player->getX() - (player->getGlobalBounds().width / 2), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				for(auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize  && it->first.second <= yTemp + blockSize ) {
						//std::cout << it->first.first << " x " << it->first.second << " y \n";
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				//put the player position to top ground position?
				player->setPosition(sf::Vector2f{ player->getX() , yTemp - blockSize + 15 });
			}
			/*else {
				player->setPosY(2000);
			}*/
		}
	}

	// player fall
	if (input == -2) {
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree.queryRange(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize, blockSize )) && type == "enemy") {
				//remove enemy from quadtree and vector enemy (so draw)
				this->quadtree.removeItem(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
				//std::cout << xTemp - blockSize << " x " << xTemp + blockSize << " x " << yTemp - blockSize << " y \n";
				for (auto it = enemyMap.begin(); it != enemyMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize) {
						enemyMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "coin") {
				//remove coin from quadtree and vector 
				this->quadtree.removeItem(player->getX(), player->getY() + (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize && it->first.first <= xTemp + blockSize  && it->first.second >= yTemp - blockSize && it->first.second <= yTemp + blockSize ) {
						//std::cout << it->first.first << " x " << it->first.second << " y \n";
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				//put the player position to top ground position?
				player->setPosition(sf::Vector2f{ player->getX() , yTemp - blockSize + 15 });
				//player->setPosY(yTemp - blockSize + 15);
			}
		}
	}

	// player jump
	if (input == 0) {
		std::tuple <std::vector<float>, std::vector<float>, std::vector<std::string>> res = this->quadtree.queryRange(player->getX(), player->getY() - (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);
		std::vector<float> temp = std::get<0>(res);
		if (temp.size() > 0) {
			float xTemp = temp[0];
			temp = std::get<1>(res);
			float yTemp = temp[0];
			std::vector<std::string> temp = std::get<2>(res);
			std::string type = temp[0];

			//Collision with enemy
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "enemy") {
				player->damage();
				//hurt the player and stop the jump
			}

			//Collision with coin
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize)) && type == "coin") {
				//remove coin from quadtree and vector 
				this->quadtree.removeItem(player->getX(), player->getY() - (player->getGlobalBounds().height / 2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height / 2);

				for (auto it = coinMap.begin(); it != coinMap.end(); ++it) {
					if (it->first.first >= xTemp - blockSize  && it->first.first <= xTemp + blockSize && it->first.second >= yTemp - blockSize  && it->first.second <= yTemp + blockSize ) {
						//std::cout << it->first.first << " x " << it->first.second << " y \n";
						coinMap.erase(std::make_pair(it->first.first, it->first.second));
						break;
					}
				}

				this->player->setScore(this->player->getScore() + 1);
			}
			//Collision with ground
			if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, blockSize , blockSize )) && type == "ground") {
				//stop the jump
				player->stopJumping();
			}
		}
	}

	//std::cout << player->getX() - blockSize << " X " << (player->getX() - blockSize) / 2 << " half \n";

	//std::cout << player->getX() + player->getGlobalBounds().width << " x " << player->getY()+player->getGlobalBounds().height << " y " << player->getGlobalBounds().width / 2 << " halfX " << player->getGlobalBounds().height / 2 << " halfY \n";
	//std::tuple <std::vector<float>, std::vector<float>> res = this->quadtree.queryRange(player->getX() + player->getGlobalBounds().width / 2, player->getY() + player->getGlobalBounds().height / 2, player->getGlobalBounds().width/2);
	//std::tuple <std::vector<float>, std::vector<float>> res = this->quadtree.queryRange(player->getX() + (player->getGlobalBounds().width/2), player->getY() + (player->getGlobalBounds().height/2), player->getGlobalBounds().width / 2, player->getGlobalBounds().height /2);
	////std::tuple <std::vector<float>, std::vector<float>> res = this->quadtree.queryRange(480, 740, 20,20);
	//std::vector<float> temp = std::get<0>(res);
	//if (temp.size() > 0) {
	//	std::cout << temp[0] << "\n";
	//	float xTemp = temp[0];
	//	temp = std::get<1>(res);
	//	float yTemp = temp[0];
	//	//std::cout << player->getX() << " X " << player->getY() << " Y \n";
	//	//std::cout << xTemp << " X " << yTemp << " Y \n";
	//	if (player->getGlobalBounds().intersects(sf::FloatRect(xTemp, yTemp, xTemp / 2, yTemp / 2))) {
	//		//std::cout << "true \n";
	//		//if player is going right
	//		if (input == 1) {
	//			player->setPosition(sf::Vector2f{ xTemp - player->getGlobalBounds().width, player->getY() });
	//			//isColliding = "right";
	//		}
	//		//if player is going left
	//		if (input == -1) {
	//			player->setPosition(sf::Vector2f{ xTemp + player->getGlobalBounds().width , player->getY() });
	//			//isColliding = "left";
	//		}
	//		if (input == -2) {
	//			// supprime l'ennemi si on le touche par le haut
	//			//delete enemyVector[i];
	//			//enemyVector.erase(enemyVector.begin() + i);
	//			std::cout << "dead";
	//		}
	//		//if is colliding right but is going left
	//		/*if (input == -1 && isColliding == "right") {
	//			player->setPosition(sf::Vector2f{ player->getX() - 20, player->getY() });
	//			isColliding = "false";
	//		}*/
	//	}
	//	else {
	//		//std::cout << "false \n";
	//	}
	//}

	/*std::tuple <std::vector<float>, std::vector<float>> collisions;
	collisions = quadtree.queryRange(enemyVector[0]->getGlobalBounds().left + (enemyVector[0]->getGlobalBounds().width / 2), enemyVector[0]->getGlobalBounds().top + (enemyVector[0]->getGlobalBounds().height / 2), enemyVector[0]->getGlobalBounds().width / 2);

	std::vector<float> temp = std::get<0>(collisions);
	std::cout << temp.size() << "\n";*/

	/*sf::FloatRect object;
	if (this->player->getGlobalBounds().intersects(object)) {
		std::cout << this->player->getGlobalBounds().intersects(object);
	}*/

	// collisions basiques
	//for (int i = 0; i < enemyVector.size(); i++) {
	//	if (this->player->getGlobalBounds().intersects(sf::FloatRect(enemyVector[i]->getGlobalBounds()))) {
	//		std::cout << "aie";
	//		if (input == 1) {
	//			player->setPosition(sf::Vector2f{ (float)enemyVector[i]->getGlobalBounds().left - player->getGlobalBounds().width, (float)player->getY() });
	//		}
	//		if (input == -1) {
	//			player->setPosition(sf::Vector2f{ (float)enemyVector[i]->getGlobalBounds().left + enemyVector[i]->getGlobalBounds().width, (float)player->getY() });
	//		}
	//		if (input == -2) {
	//			// supprime l'ennemi si on le touche par le haut
	//			delete enemyVector[i];
	//			enemyVector.erase(enemyVector.begin() + i);
	//			std::cout << "dead";
	//		}
	//	}
	//	
	//}

	//for (int i = 0; i < coinVector.size(); i++) {
	//	if (this->player->getGlobalBounds().intersects(sf::FloatRect(coinVector[i]->getGlobalBounds()))) {

	//		//supprime la pièce si on la touche
	//		delete coinVector[i];
	//		coinVector.erase(coinVector.begin() + i);
	//		this->player->setScore(this->player->getScore() + 1);

	//		std::cout << "score";
	//	}
	//}
	
	//peut faire ramer le jeu
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
