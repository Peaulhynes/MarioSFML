#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "AssetsManager.h"
#include "Map.h"

class GUI
{
public:
	GUI(AssetsManager& assets, sf::RenderWindow& window, Map *map);
	~GUI();


	void update(int gameStatus);
	/* Draw GUI on specified window. */
	void draw(sf::RenderWindow& window);

private:
	Map *map;
	sf::Text scoreText;
	sf::Text lifeText;
	bool active;
};

#endif
