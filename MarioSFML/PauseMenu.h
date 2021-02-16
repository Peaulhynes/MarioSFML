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

	/* Get PauseMenu activity state. */
	bool getActive();

	/* Start pause. */
	void start();

	/* Switch PauseMenu activity state. */
	void switchMode();

	/* Draw PauseMenu on specified window. */
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text message;
	bool active;
};

#endif // !PAUSEMENU_H




