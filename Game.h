#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

class Game {
public:
	enum pieces {
		NOUGHT_PIECE,
		CROSS_PIECE,
		PIECE_TOTAL
	};
public:
	Game();
	~Game();
	bool init();
	void destroy();
	bool loadMedia();
	void updateScreen();
public:
	bool checkQuit(SDL_Event event);
	bool checkKeyboard(SDL_Event event);
	void keyboardEvent(SDL_Event event);
	void placePiece();
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;	
private:
	SDL_Window * window;
	SDL_Surface* screenSurface;
	SDL_Surface* currentSurface;
	SDL_Surface* pieceStore[PIECE_TOTAL];
	bool xTurn;
private:
	SDL_Surface * loadSurface(string path);
};

