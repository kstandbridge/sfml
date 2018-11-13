#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks(); // The number of tickets since execution

		game->handleEvents();	// handle any user input
		game->update();			// update all object eh, position, etc
		game->render();			// render changes to the display

		frameTime = SDL_GetTicks() - frameStart; // How long this iteration took

		if(frameDelay > frameTime) // Do we need to delay the next iteration
		{
			SDL_Delay(frameDelay - frameTime); // Delay by the difference
		}
	}

	game->clean();
	delete game;

	return 0;
}
