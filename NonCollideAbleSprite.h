#ifndef NONCOLLIDEABLE_H
#define NONCOLLIDEABLE_H
#include "Sprite.h"
namespace minMotor {
	class NonCollideAbleSprite : public Sprite
	{
	protected:
		NonCollideAbleSprite(int x, int y, int w, int h);
	private:
		NonCollideAbleSprite(const NonCollideAbleSprite&) = delete;
		const NonCollideAbleSprite& operator=(const NonCollideAbleSprite&) = delete;
	};
}
#endif