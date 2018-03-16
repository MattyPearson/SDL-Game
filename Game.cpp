#include "Game.h"


using namespace std;


Game::Game() :window(NULL), screenSurface(NULL), currentSurface(NULL), xTurn(true) {

}


Game::~Game()
{
}

bool Game::init() {

	//nitialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialise." << endl;
		return false;
	}

	window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit();
		return false;
	}

	//Initialise PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "SDL_image could not initialise." << endl;
		return false;
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface(window);

	return true;
}

void Game::destroy() {
		
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}

bool Game::loadMedia() {
		
	currentSurface = loadSurface("assets/WhiteBack.png");

	pieceStore[NOUGHT_PIECE] = loadSurface("assets/nought.png");
	pieceStore[CROSS_PIECE] = loadSurface("assets/cross.png");

	return true;
}

void Game::updateScreen() {
	
	SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
}

bool Game::checkQuit(SDL_Event event) {

	if (event.type == SDL_QUIT) {
		return true;
	}

	return false;
}


bool Game::checkKeyboard(SDL_Event event) {

	if (event.type == SDL_KEYDOWN) {
		return true;
	}

	return false;
}

void Game::keyboardEvent(SDL_Event event) {
	
}

void Game::placePiece() {
	if (xTurn) {
		currentSurface = pieceStore[CROSS_PIECE];
		xTurn = false;
		return;
	}
	else {
		currentSurface = pieceStore[NOUGHT_PIECE];
		xTurn = true;
		return;
	}
	
}

SDL_Surface * Game::loadSurface(string path) {
	//The final optimsed surface
	SDL_Surface* optimisedSurface = NULL;

	//Loading image of specified path
	SDL_Surface * loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image from " << path.c_str() << endl;
	}
	else {
		//Convert surface to screen format
		optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (optimisedSurface == NULL) {
			cout << "Unable to optimse image" << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimisedSurface;
}




