//Code written by Christian Neij
#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
#include <SDL_ttf.h>
namespace minMotor {
	class System
	{
	public:
		System();
		~System();
		SDL_Renderer* getRen() const;
		TTF_Font* getFont() const;
		void initializeWindow(int w, int h);
	private:
		SDL_Window* win;
		SDL_Renderer* ren;
		TTF_Font* font;
	};

	extern System sys;
}
#endif
