#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "AssetsManager.h"


class PauseMenu;
class Map;

class Game
{
public:
    sf::View view;
    sf::RenderWindow window;
    AssetsManager assets;
    PauseMenu* pauseMenu;
    Map* map;

public:

    Game();
    ~Game();
    void loadTextures();
    void loadFonts();
    void gameLoop();

};

#endif // !GAME_H