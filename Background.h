//Code written by Christian Neij
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "NonMoveableSprite.h"
#include <SDL_image.h>
#include "System.h"
namespace minMotor {
	class Background : public NonMoveableSprite
	{
	public:
		static Background* getInstance(int x, int y, int w, int h, const char* upIconPath);
		void draw() const;
		~Background();
	private:
		Background(int x, int y, int w, int h, const char* backgroundPath);
		SDL_Texture* texture;
	};
}
#endif
