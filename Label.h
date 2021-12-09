#ifndef LABEL_H
#define LABEL_H
#include <string>
#include <SDL.h>
#include "NonCollideAbleSprite.h"
namespace minMotor {
	class Label : public NonCollideAbleSprite
	{
	public:
		static Label* getInstance(int x, int y, int w, int h, std::string txt);
		void draw() const;
		std::string getText() const;
		void setText(std::string newText);
		~Label();
	protected:
		Label(int x, int y, int w, int h, std::string txt);
		std::string text;
		SDL_Texture* texture;
	};
}
#endif