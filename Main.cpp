// Data includes.
#include "Game.h"

int main(int argc, char * argv[])
{
	// Create the game.
	MainGame::Game game;

	// Start the main game loop, quit when the loop exits.
	game.Run();
	return 0;
}