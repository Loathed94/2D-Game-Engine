//Code written by Christian Neij
#include "Background.h"
namespace minMotor {
	Background* Background::getInstance(int x, int y, int w, int h, const char* backgroundPath) {
		return new Background(x, y, w, h,backgroundPath);
	}
	void Background::draw() const {
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
	}
	Background::~Background()
	{
		SDL_DestroyTexture(texture);
	}
	Background::Background(int x, int y, int w, int h, const char* backgroundPath) : NonMoveableSprite(x, y, w, h) {
		texture = IMG_LoadTexture(sys.getRen(), backgroundPath);
	}
}
