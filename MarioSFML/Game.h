#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class View;
class PauseMenu;
class GameOverMenu;
class Map;
class GUI;

class Game
{
public:
    
    sf::RenderWindow window;
    AssetsManager assets;
    PauseMenu* pauseMenu;
    GameOverMenu* gameOverMenu;
    GUI* gameUi;
    Map* map;

    sf::View mapView;

    std::pair<float, sf::Sprite> farBackground;
    std::pair<float, sf::Sprite> nearBackground;
    sf::View farBackgroundView;
    sf::View nearBackgroundView;

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