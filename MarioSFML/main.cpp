#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    Game* game = new Game();
    game->gameLoop();
    delete game;
    game = nullptr;

    return EXIT_SUCCESS;
}