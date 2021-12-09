//Code written by Christian Neij
#ifndef BUTTON_H
#define BUTTON_H
#include "NonMoveableSprite.h"
#include <SDL.h>
#include <string>
namespace minMotor {
	class Button : public NonMoveableSprite
	{
	public:
		void mouseDown(const SDL_Event&);
		void mouseUp(const SDL_Event&);
		void draw() const;
		virtual void perform() {}
		virtual bool wasItActivated() = 0;
		~Button();
	protected:
		Button(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath);
	private:
		std::string text;
		SDL_Texture* texture;
		SDL_Texture* upIcon, * downIcon;
		bool isDown = false;
		Button(const Button&) = delete;
		const Button& operator=(const Button&) = delete;
	};
}
#endif
