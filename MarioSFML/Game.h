#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

class View;
class PauseMenu;
class Map;

class Game
{
public:
    
    sf::RenderWindow window;
    AssetsManager assets;
    PauseMenu* pauseMenu;
    Map* map;
    View* view;

public:

    Game();
    ~Game();
    void loadTextures();
    void loadFonts();
    void gameLoop();

};

#endif // !GAME_H