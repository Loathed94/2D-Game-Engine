//Code written by Christian Neij
#include "Session.h"
#include "MoveableSprite.h"
#include <SDL_image.h>
#include "System.h"
#include "NonMoveableSprite.h"
#include "Label.h"
#include "Button.h"
#include "NonCollideAbleSprite.h"
#include <time.h>
#include <iostream>
#define BUTTON_UP_PATH "C:/Users/chris/Documents/CPROG-Projekt/buttonUp1.png"
#define BUTTON_DOWN_PATH "C:/Users/chris/Documents/CPROG-Projekt/buttonDown1.png"
#define BACKGROUND_PATH "C:/Users/chris/Documents/CPROG-Projekt/background.png"
#define TABLE_PATH "C:/Users/chris/Documents/CPROG-Projekt/Table.png"
#define PERSON_PATH "C:/Users/chris/Documents/CPROG-Projekt/Player.png"
#define NPC_PATH "C:/Users/chris/Documents/CPROG-Projekt/NPC.png"
#define SENSOR_PAD_PATH "C:/Users/chris/Documents/CPROG-Projekt/sensorPad.png"
using namespace minMotor;
Session gameLoop;
Label* walletLabel;
void blackJackLoop();
class ExitLoopButton : public Button
{
public:
	static ExitLoopButton* getInstance(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath);
	bool wasItActivated() { return quit; }
private:
	ExitLoopButton(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath) :Button(x, y, w, h, txt, upIconPath, downIconPath), quit(false) {

	}
	void perform() { quit = true; }
	bool quit;
};
class Table : public NonMoveableSprite
{
public:
	static Table* getInstance(int x, int y, int w, int h);
	void draw() const {
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
	}
	~Table()
	{
		SDL_DestroyTexture(texture);
	}
private:
	Table(int x, int y, int w, int h) : NonMoveableSprite(x, y, w, h) {
		texture = IMG_LoadTexture(sys.getRen(), TABLE_PATH);
	}
	SDL_Texture* texture;
};
class NPC : public MoveableSprite
{
public:
	static NPC* getInstance(int x, int y, int w, int h);
	void draw() const{
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
	}
	void tick() {
		if (goingLeft) {
			rect.x = rect.x - 1;
			bool didCollide = collisionCheck(SDLK_LEFT, gameLoop);
			if (rect.x <= startPoint - 20) { goingLeft = false; }
			else if (didCollide) { goingLeft = false; }
		}
		else {
			rect.x = rect.x + 1;
			bool didCollide = collisionCheck(SDLK_RIGHT, gameLoop);
			if (rect.x >= startPoint + 20) { goingLeft = true; }
			else if (didCollide) { goingLeft = true; }
		}
	}
private:
	bool goingLeft;
	int startPoint;
	NPC(int x, int y, int w, int h) : MoveableSprite(x, y, w, h) {
		goingLeft = true;
		startPoint = x;
		texture = IMG_LoadTexture(sys.getRen(), NPC_PATH);
	}
	SDL_Texture* texture;
	bool collisionCheck(const SDL_Keycode& key, const Session& gameLoop) {
		for (Sprite* s : gameLoop.getSprites()) {
			if (s == this) { continue; }
			SDL_bool results = SDL_HasIntersection(&rect, &(s->getRect()));
			if ((results == SDL_TRUE) && (s->doesItCollide())) {
				switch (key) {
					case SDLK_RIGHT: move(-5, 0); break;
					case SDLK_LEFT: move(5, 0); break;
					case SDLK_UP: move(0, 5); break;
					case SDLK_DOWN: move(0, -5); break;
				}
				return true;
			}
		}
		return false;
	}
};
class Person : public MoveableSprite
{
public:
	static Person* getInstance(int x, int y, int w, int h);
	void draw() const{
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
	}
	~Person()
	{
		SDL_DestroyTexture(texture);
	}
	void keyDown(const SDL_Event& eve) {
		if (eve.key.keysym.sym == SDLK_r) {
			toggleRunning();
		}
		if (!running) {
			switch (eve.key.keysym.sym) {
			case SDLK_RIGHT: move(5, 0); break;
			case SDLK_LEFT: move(-5, 0); break;
			case SDLK_UP: move(0, -5); break;
			case SDLK_DOWN: move(0, 5); break;
			}
		}
		else {
			switch (eve.key.keysym.sym) {
			case SDLK_RIGHT: move(8, 0); break;
			case SDLK_LEFT: move(-8, 0); break;
			case SDLK_UP: move(0, -8); break;
			case SDLK_DOWN: move(0, 8); break;
			}
		}
		collisionCheck(eve.key.keysym.sym, gameLoop);
	}
	void toggleRunning() { running = !running; }
	static int getWalletBalance();
	static void manipulateWallet(int change);
private:
	static int wallet;
	bool running;
	Person(int x, int y, int w, int h) : MoveableSprite(x,y,w,h),running(false) {
		texture = IMG_LoadTexture(sys.getRen(), PERSON_PATH);
	}
	SDL_Texture* texture;
	bool collisionCheck(const SDL_Keycode& key, const Session& gameLoop) {
		for (Sprite* s : gameLoop.getSprites()) {
			if (s == this) { continue; }
			SDL_bool results = SDL_HasIntersection(&rect, &(s->getRect()));
			if ((results == SDL_TRUE) && (s->doesItCollide())) {
				if (!running) {
					switch (key) {
					case SDLK_RIGHT: move(-5, 0); break;
					case SDLK_LEFT: move(5, 0); break;
					case SDLK_UP: move(0, 5); break;
					case SDLK_DOWN: move(0, -5); break;
					}
				}
				else {
					switch (key) {
					case SDLK_RIGHT: move(-8, 0); break;
					case SDLK_LEFT: move(8, 0); break;
					case SDLK_UP: move(0, 8); break;
					case SDLK_DOWN: move(0, -8); break;
					}
				}
				return true;
			}
		}
		return false;
	}
};
class BlackJackButton : public Button
{
public:
	static BlackJackButton* getInstance(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath, int amount);
	bool wasItActivated() { return performed; }
	bool didPlayerWin() { return won; }
	bool didPlayerLose() { return lose; }
private:
	BlackJackButton(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath, int amount) :Button(x, y, w, h, txt, upIconPath, downIconPath), betAmount(amount), performed(false), won(false), lose(false) {

	}
	bool performed;
	bool lose;
	bool won;
	const int betAmount;
	void perform() {
		if (Person::getWalletBalance() < betAmount) {
			return;
		}
		Person::manipulateWallet(-betAmount);
		std::srand(time(0));
		int winOrLose = rand() % 4;
		if (winOrLose == 0) {
			won = true;
			Person::manipulateWallet(2 * betAmount);
		}
		else { lose = true; }
		performed = true;
	}
};
class SensorPad : public NonCollideAbleSprite
{
public:
	static SensorPad* getInstance(int x, int y, int w, int h);
	void draw() const {
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
	}
	bool isItSteppedOn() {
		for (Sprite* s : gameLoop.getSprites()) {
			if (s == this) { continue; }
			SDL_bool results = SDL_HasIntersection(&rect, &(s->getRect()));
			if (results == SDL_TRUE) {
				return true;
			}
		}
		return false;
	}
	void keyDown(const SDL_Event& eve) {
		bool steppedOn = isItSteppedOn();
		if (steppedOn && !activated) {
			activated = true;
			blackJackLoop();
		}
		else if (!steppedOn && activated) {
			activated = false;
		}
	}
	~SensorPad()
	{
		SDL_DestroyTexture(texture);
	}
private:
	bool activated;
	SensorPad(int x, int y, int w, int h) : NonCollideAbleSprite(x, y, w, h), activated(false) {
		texture = IMG_LoadTexture(sys.getRen(), SENSOR_PAD_PATH);
	}
	SDL_Texture* texture;
};
class ExitPad : public NonCollideAbleSprite {
public:
	static ExitPad* getInstance(int x, int y, int w, int h);
	void draw() const {
		SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
		SDL_RenderCopy(sys.getRen(), textTexture, NULL, &getRect());
	}
	bool isItSteppedOn() {
		for (Sprite* s : gameLoop.getSprites()) {
			if (s == this) { continue; }
			SDL_bool results = SDL_HasIntersection(&rect, &(s->getRect()));
			if (results == SDL_TRUE) {
				return true;
			}
		}
		return false;
	}
	void keyDown(const SDL_Event& eve) {
		bool steppedOn = isItSteppedOn();
		if (steppedOn) {
			gameLoop.exit();
		}
	}
	~ExitPad()
	{
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(textTexture);
	}
private:
	SDL_Texture* textTexture;
	ExitPad(int x, int y, int w, int h) : NonCollideAbleSprite(x, y, w, h) {
		texture = IMG_LoadTexture(sys.getRen(), SENSOR_PAD_PATH);
		SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), "Exit", { 0,0,0 });
		textTexture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
		SDL_FreeSurface(surf);
	}
	SDL_Texture* texture;
};
BlackJackButton* BlackJackButton::getInstance(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath, int amount) {
	return new BlackJackButton(x, y, w, h, txt, upIconPath, downIconPath, amount);
}
ExitLoopButton* ExitLoopButton::getInstance(int x, int y, int w, int h, std::string txt, const char* upIconPath, const char* downIconPath) {
	return new ExitLoopButton(x, y, w, h, txt, upIconPath, downIconPath);
}
SensorPad* SensorPad::getInstance(int x, int y, int w, int h) {
	return new SensorPad(x, y, w, h);
}
ExitPad* ExitPad::getInstance(int x, int y, int w, int h) {
	return new ExitPad(x, y, w, h);
}
Person* Person::getInstance(int x, int y, int w, int h){
	return new Person(x, y, w, h);
}
int Person::getWalletBalance() { return wallet; }
void Person::manipulateWallet(int change) { wallet += change; }
int Person::wallet = 5000;
NPC* NPC::getInstance(int x, int y, int w, int h) {
	return new NPC(x, y, w, h);
}
Table* Table::getInstance(int x, int y, int w, int h) {
	return new Table(x, y, w, h);
}
void blackJackLoop() {
	std::vector<Button*> buttons;
	ExitLoopButton* exitButton = ExitLoopButton::getInstance(290, 600, 80, 50, "Exit", BUTTON_UP_PATH, BUTTON_DOWN_PATH);
	buttons.push_back(exitButton);
	bool exit = false;
	Label* gameOutput;
	while (!exit) {
		BlackJackButton* button50 = BlackJackButton::getInstance(20, 600, 80, 50, "50", BUTTON_UP_PATH, BUTTON_DOWN_PATH, 50);
		BlackJackButton* button250 = BlackJackButton::getInstance(110, 600, 80, 50, "250", BUTTON_UP_PATH, BUTTON_DOWN_PATH, 250);
		BlackJackButton* button1000 = BlackJackButton::getInstance(200, 600, 80, 50, "1000", BUTTON_UP_PATH, BUTTON_DOWN_PATH, 1000);
		buttons.push_back(button50);
		buttons.push_back(button250);
		buttons.push_back(button1000);
		SDL_Event eve;
		bool win = false;
		bool lose = false;
		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
			case SDL_MOUSEBUTTONDOWN:
				for (Button* s : buttons) {
					s->mouseDown(eve);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				for (Button* s : buttons) {
					s->mouseUp(eve);
				}
				if (buttons.at(0)->wasItActivated()) {
					exit = true;
				}
				else if (buttons.at(1)->wasItActivated() || buttons.at(2)->wasItActivated() || buttons.at(3)->wasItActivated()) {
					walletLabel->setText(std::to_string(Person::getWalletBalance()));
				}
				if (button50->didPlayerWin() || button250->didPlayerWin() || button1000->didPlayerWin()) {
					win = true;
				}
				else if (button50->didPlayerLose() || button250->didPlayerLose() || button1000->didPlayerLose()) {
					lose = true;
				}
				break;
			}
		}
		if (win) {
			gameOutput = Label::getInstance(50, 100, 550, 100, "Player wins! Congratulations!");
		}
		else if (lose) {
			gameOutput = Label::getInstance(50, 100, 500, 100, "Player loses! Tough luck!");
		}
		else {
			gameOutput = Label::getInstance(50, 100, 700, 100, "What are you waiting for!? Try again!");
		}
		SDL_RenderClear(sys.getRen());
		walletLabel->draw();
		gameOutput->draw();
		for (Button* s : buttons) {
			s->draw();
		}
		SDL_RenderPresent(sys.getRen());
		if (win || lose) {
			SDL_Delay(1250);
		}
		buttons.pop_back();
		buttons.pop_back();
		buttons.pop_back();
		delete gameOutput;
		delete button50;
		delete button250;
		delete button1000;
	}
}
void quitShortcut() {
	gameLoop.exit();
}
void addShortcuts() {
	FuncPointer quit = quitShortcut;
	gameLoop.getShortcuts().add(SDLK_ESCAPE,quit);
}
void createSprites() {
	Background* bg = Background::getInstance(0, 0, 1000, 700, BACKGROUND_PATH);
	SensorPad* sp = SensorPad::getInstance(325,346,40,40);
	Person* pers = Person::getInstance(20, 20, 30, 30);
	NPC* npc = NPC::getInstance(330, 268, 30, 30);
	walletLabel = Label::getInstance(900,0,100,100,std::to_string(Person::getWalletBalance()));
	Table* table1 = Table::getInstance(300, 300, 90, 45);
	Table* table2 = Table::getInstance(500, 300, 90, 45);
	Table* table3 = Table::getInstance(700, 300, 90, 45);
	ExitPad* exit = ExitPad::getInstance(400, 650, 200, 50);
	gameLoop.setBackground(bg);
	gameLoop.add(sp);
	gameLoop.add(pers);
	gameLoop.add(walletLabel);
	gameLoop.add(table1);
	gameLoop.add(table2);
	gameLoop.add(table3);
	gameLoop.add(npc);
	gameLoop.add(exit);
}
int main(int argc, char** argv) {
	sys.initializeWindow(1000, 700);
	createSprites();
	addShortcuts();
	gameLoop.run();
	return 0;
}



