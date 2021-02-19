#ifndef GAMEUI_H
#define GAMEUI_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include "AssetsManager.h"
#include "Map.h"

class GameUI
{
public:
	GameUI();
	~GameUI() = default;

	/* Update UI status depending on gameStatus. */
	virtual void update(int gameStatus) = 0;

	/* Draw UI on specified window. */
	virtual void draw(sf::RenderWindow& window) = 0;

	/* Get activity of widget */
	bool getActive();

protected:
	bool active;
};

/* --------------- MainUI --------------- */

class MainUI : public GameUI
{
public:
	MainUI(AssetsManager& assets, sf::RenderWindow& window, Map* map);
	~MainUI() = default;
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	Map* map;
	sf::RectangleShape box;
	sf::Text scoreText;
	sf::Text lifeText;
};

/* --------------- StartMenu --------------- */

class StartMenu : public GameUI
{
public:
	StartMenu(AssetsManager& assets, sf::RenderWindow& window);
	~StartMenu() = default;
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text title;
	sf::Text message1;
	sf::Text message2;
	sf::Text credits;
};

/* --------------- PauseMenu --------------- */

class PauseMenu : public GameUI
{
public:
	PauseMenu(AssetsManager& assets, sf::RenderWindow& window);
	~PauseMenu() = default;
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text title;
};

/* --------------- GameOverMenu --------------- */

class GameOverMenu : public GameUI
{
public:
	GameOverMenu(AssetsManager& assets, sf::RenderWindow& window);
	~GameOverMenu() = default;
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text title; 
	sf::Text message1;
	sf::Text message2;
};

/* --------------- VictoryMenu --------------- */

class VictoryMenu : public GameUI
{
public:
	VictoryMenu(AssetsManager& assets, sf::RenderWindow& window);
	~VictoryMenu() = default;
	void update(int gameStatus);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape overlay;
	sf::Text title;
	sf::Text message1;
	sf::Text message2;
};

#endif // !GAMEUI_H


