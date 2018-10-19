#include "Common/Window.h"

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	while(!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}

	return EXIT_SUCCESS;
}