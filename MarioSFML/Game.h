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
class Map;

class Game
{
public:
    
    sf::RenderWindow window;
    AssetsManager assets;
    StartMenu* startMenu;
    PauseMenu* pauseMenu;
    GameOverMenu* gameOverMenu;
    VictoryMenu* victoryMenu;
    MainUI* mainUI;
    Map* map;

    sf::View mapView;

    std::pair<float, sf::Sprite> farBackground;
    std::pair<float, sf::Sprite> nearBackground;
    sf::View farBackgroundView;
    sf::View nearBackgroundView;

    int status;

public:

    Game();
    ~Game();

    /* Load all game textures. */
    void loadTextures();

    /* Load all game fonts. */
    void loadFonts();

    /* Main loop of the game. */
    void gameLoop();

};

#endif // !GAME_H