#include "Shortcuts.h"
#include <iostream>
namespace minMotor {
	void Shortcuts::add(const SDL_Keycode& key, FuncPointer func) {
		shortcuts.insert(std::make_pair(key, func));
	}
	Shortcuts::Shortcuts() {
	}
	FuncPointer Shortcuts::get(const SDL_Keycode& key) const {
		return shortcuts.at(key);
	}
	/*void Shortcuts::dump() {
		for (std::map<SDL_Keycode, void (*)()>::iterator iter = shortcuts.begin(); iter != shortcuts.end(); iter++) {
			std::cout << iter->first << " " << iter->second << std::endl;
		}
	}*/
}