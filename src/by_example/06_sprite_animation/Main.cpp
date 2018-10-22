#include "Common/Window.h"

#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	while(!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}

	return EXIT_SUCCESS;
}