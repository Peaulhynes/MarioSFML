#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"
#include "Game.h"

class GameOverMenu
{
public:
	GameOverMenu(AssetsManager& assets, sf::RenderWindow& window);
	~GameOverMenu();
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text message;
	bool active;
};

#endif // !GAMEOVERMENU_H




