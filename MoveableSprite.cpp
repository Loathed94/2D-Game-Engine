//Code written by Christian Neij
#include "MoveableSprite.h"
#include <iostream>
namespace minMotor {
	MoveableSprite::MoveableSprite(int x, int y, int w, int h) :Sprite(x, y, w, h) {
	}
	void MoveableSprite::move(int x, int y) {
		rect.x += x;
		rect.y += y;
	}
}
