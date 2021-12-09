#ifndef MOVE_SPRITE_H
#define MOVE_SPRITE_H
#include "Sprite.h"
#include "Session.h"
namespace minMotor {
	class MoveableSprite : public Sprite
	{
	public:

	protected:
		MoveableSprite(int x, int y, int w, int h);
		virtual void tick() {}
		void move(int x, int y);
		virtual bool collisionCheck(const SDL_Keycode& key, const Session& gameLoop) = 0;
	private:
		MoveableSprite(const MoveableSprite&) = delete;
		const MoveableSprite& operator=(const MoveableSprite&) = delete;
	};
}
#endif