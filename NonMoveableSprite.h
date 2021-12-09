//Code written by Christian Neij
#ifndef NON_MOVE_SPRITE_H
#define NON_MOVE_SPRITE_H
#include "Sprite.h"
namespace minMotor {
	class NonMoveableSprite : public Sprite
	{
	protected:
		NonMoveableSprite(int x, int y, int w, int h);
	private:
		NonMoveableSprite(const NonMoveableSprite&) = delete;
		const NonMoveableSprite& operator=(const NonMoveableSprite&) = delete;
	};
}
#endif
