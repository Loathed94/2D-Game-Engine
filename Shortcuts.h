#ifndef SHORTCUTS_H
#define SHORTCUTS_H
#include <SDL.h>
#include <map>
namespace minMotor {
	typedef void (*FuncPointer)();
	class Shortcuts
	{
	public:
		Shortcuts();
		FuncPointer get(const SDL_Keycode& key)const;
		void add(const SDL_Keycode& key, FuncPointer func);
		//void dump();  Användes bara för att testa något.
	private:
		std::map<SDL_Keycode, void (*)()> shortcuts;
	};
}
#endif