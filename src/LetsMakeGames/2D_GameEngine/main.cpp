#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->init("BirchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())
	{
		// handle any user input
		game->handleEvents();
		// update all object eh, position, etc
		game->update();
		// render changes to the display
		game->render();
	}

	game->clean();

	delete game;

	return 0;
}
