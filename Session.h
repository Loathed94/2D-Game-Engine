//Code written by Christian Neij
#ifndef SESSION_H
#define SESSION_H
#include <vector>
#include "Sprite.h"
#include "Shortcuts.h"
#include "Background.h"
namespace minMotor {
	class Session
	{
	public:
		Session();
		~Session();
		void run();
		void add(Sprite* sprite);
		void remove(Sprite* sprite);
		void setBackground(const Background* bg) { background = bg; }
		const std::vector<Sprite*> getSprites() const{ return sprites; }
		void exit() { running = false; }
		Shortcuts& getShortcuts() { return shortcuts; }
	private:
		const Background* background;
		std::vector<Sprite*> sprites;
		std::vector<Sprite*> newlyAdded;
		std::vector<Sprite*> toBeRemoved;
		bool running;
		Shortcuts shortcuts;
	};
}
#endif
