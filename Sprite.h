#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
namespace minMotor {
	class Sprite
	{
	public:
		virtual void mouseDown(const SDL_Event& eve) {}
		virtual void mouseUp(const SDL_Event& eve) {}
		virtual void keyDown(const SDL_Event& eve) {}
		virtual void keyUp(const SDL_Event& eve) {}
		virtual void draw() const = 0;
		virtual void tick() {}
		bool doesItCollide() { return doesCollide; }
		const SDL_Rect& getRect() const;
		virtual ~Sprite() {}
	protected:
		Sprite(int x, int y, int w, int h, bool doesItCollide=true);
		SDL_Rect rect;
	private:
		bool doesCollide;
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
	};
}
#endif