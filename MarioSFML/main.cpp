#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
	Game* game = new Game();
	game->gameLoop();
	delete game;
	game = nullptr;

	return EXIT_SUCCESS;
}

