//Code written by Christian Neij
#include "Sprite.h"
namespace minMotor {
	Sprite::Sprite(int x, int y, int w, int h, bool doesItCollide) :rect{ x,y,w,h },doesCollide(doesItCollide)
	{
	}
	const SDL_Rect& Sprite::getRect() const {
		return rect;
	}

}
