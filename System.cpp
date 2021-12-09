#include "System.h"

namespace minMotor{
	System::System() : win(NULL), ren(NULL){
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 14);
	}
	void System::initializeWindow(int w, int h) {
		win = SDL_CreateWindow("Min Motor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}
	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}
	SDL_Renderer* System::getRen() const {return ren;}
	TTF_Font* System::getFont() const {return font;}
	System sys;
}