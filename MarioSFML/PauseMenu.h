#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <SFML/Graphics.hpp>

class PauseMenu
{
private:
	sf::RectangleShape pauseOverlay;
	sf::Text message;
	bool active;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();
	bool getActive();
	void start();
	void end();
	void switchMode();
	void drawTo(sf::RenderWindow& window);
};

#endif // !PAUSEMENU_H




