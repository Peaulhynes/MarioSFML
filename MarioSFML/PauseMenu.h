#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Game.h"

class PauseMenu
{
public:
	PauseMenu(AssetsManager& assets, sf::RenderWindow& window);
	~PauseMenu();
	bool getActive();
	void start();
	void end();
	void switchMode();
	void draw(sf::RenderWindow& window);
private:
	
	sf::RectangleShape overlay;
	sf::Text message;
	bool active;
};

#endif // !PAUSEMENU_H




