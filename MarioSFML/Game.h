#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class View;
class PauseMenu;
class Map;
class GUI;

class Game
{
public:
    
    sf::RenderWindow window;
    AssetsManager assets;
    PauseMenu* pauseMenu;
    GUI* gameUi;
    Map* map;

    sf::View mapView;

    sf::Sprite layerBg1;
    sf::Sprite layerBg2;
    sf::Sprite layerBg3;
    sf::View layerBg1View;
    sf::View layerBg2View;
    sf::View layerBg3View;

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