//Code written by Christian Neij
#include "Session.h"
#include "System.h"
#include <SDL.h>
#include "MoveableSprite.h"
#include <stdexcept>
#include <iostream>
#define FPS 60
namespace minMotor {
	Session::Session() : background(NULL){
		running = true;
	}
	void Session::add(Sprite* sprite) {
		newlyAdded.push_back(sprite);
	}
	void Session::remove(Sprite* sprite) {
		toBeRemoved.push_back(sprite);
	}
	void Session::run() {
		Uint32  tickInterval = 1000 / FPS;
		while (running) {
			int nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite* s : sprites) {
						s->mouseDown(eve);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					for (Sprite* s : sprites) {
						s->mouseUp(eve);
					}
					break;
				case SDL_KEYDOWN:
					try 
				{
						FuncPointer func = shortcuts.get(eve.key.keysym.sym);
						func();
				}
					catch(const std::out_of_range){
						for (Sprite* s : sprites) {
							s->keyDown(eve);
						}
					}
					break;
				case SDL_KEYUP:
					for (Sprite* s : sprites) {
						s->keyUp(eve);
					}
					break;

				}
			}
			SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
			SDL_RenderClear(sys.getRen());
			for (Sprite* s : sprites) {
				s->tick();
			}
			for (Sprite* s : newlyAdded) {
				sprites.push_back(s);
			}
			newlyAdded.clear();
			for (Sprite* s : toBeRemoved) {
				for (std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();) {
					if (*i == s) {
						i = sprites.erase(i);
						delete s;
					}
					else {
						i++;
					}
				}
			}
			toBeRemoved.clear();
			background->draw();
			for (Sprite* s : sprites)
				s->draw();
			SDL_RenderPresent(sys.getRen());
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0) { SDL_Delay(delay); }
		} 
	}
	Session::~Session() {
		for (Sprite* s : sprites) {
			delete s;
		}
	}
}
