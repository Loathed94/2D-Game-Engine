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
		//void dump();  Anv�ndes bara f�r att testa n�got.
	private:
		std::map<SDL_Keycode, void (*)()> shortcuts;
	};
}
#endif