#pragma once

#include <SDL.h>

namespace cellular_automaton {

class CellularAutomatonApp {
public:
	static CellularAutomatonApp* getInstance();
	int execute(int argc, char* argv[]);

private:
	bool init();
	void pollEvents();
	void processEvent(SDL_Event* event);
	void loop();
	void render();
	void breate();
	void cleanup();

	static CellularAutomatonApp instance_;
	bool running_ = false;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* primarySurface_ = nullptr;

	static const int windowWidth_ = 1024;
	static const int windowHeight_ = 768;
};

}
