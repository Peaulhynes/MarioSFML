#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <math.h>  
#include "AssetsManager.h"

enum GameStatus {
    START,
    INGAME,
    PAUSE,
    GAMEOVER,
    VICTORY
};

class View;
class StartMenu;
class PauseMenu;
class GameOverMenu;
class VictoryMenu;
class MainUI;
class GameUI;
class Map;

class Game
{
public:
    
    sf::RenderWindow window;
    std::map<std::string, GameUI*>widgets;
    AssetsManager assets;
    Map* map;
    
    std::pair<float, sf::Sprite> farBackground;
    std::pair<float, sf::Sprite> nearBackground;

    sf::View farBackgroundView;
    sf::View nearBackgroundView;
    sf::View mapView;
    int status;

public:

    Game();
    ~Game();

    /* Load all game textures. */
    void loadTextures();

    /* Load all game fonts. */
    void loadFonts();

    /* Load all game maps. */
    void loadMaps();

    /* Restart the game. */
    void restart();

    /* Main loop of the game. */
    void gameLoop();

};

#endif // !GAME_H