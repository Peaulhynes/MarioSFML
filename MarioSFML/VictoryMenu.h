#ifndef VICTORYMENU_H
#define VICTORYMENU_H
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Game.h"

class VictoryMenu
{
public:
	VictoryMenu(AssetsManager& assets, sf::RenderWindow& window);
	~VictoryMenu();
	bool getActive();
	void start();
	void end();
	void draw(sf::RenderWindow& window);
private:

	sf::RectangleShape overlay;
	sf::Text message;
	bool active;
};

#endif // !VICTORYMENU_H




