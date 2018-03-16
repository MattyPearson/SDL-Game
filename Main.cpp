#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
using namespace std;



int main(int argc, char * argv[])
{
	Game game;

	if (!game.init()) {
		cout << "SDL init failed." << endl;
	}

	if (!game.loadMedia()) {
		cout << "Failed to load media!" << endl;
	}

	bool quit = false;
	SDL_Event event;

	while (!quit) {

		while (SDL_PollEvent(&event) != 0) {

			if (game.checkQuit(event)) {
				quit = true;
			} 
			if (game.checkKeyboard(event)) {
				game.placePiece();
			}
		}
		
		game.updateScreen();
	}

	game.destroy();

	
	return 0;
}


