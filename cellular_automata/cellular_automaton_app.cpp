#include "cellular_automaton_app.h"

namespace cellular_automaton {

CellularAutomatonApp CellularAutomatonApp::instance_;

CellularAutomatonApp* CellularAutomatonApp::getInstance() {
	return &instance_;
}

int CellularAutomatonApp::execute(int argc, char* argv[]) {
	running_ = true;
	if (!init()) return 0;

	while (running_) {
		pollEvents();
		loop();
		render();
		breate();
	}

	cleanup();
	return 1;
}

bool CellularAutomatonApp::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//Log("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		//Log("Unable to Init hinting: %s", SDL_GetError());
	}

	if ((window_ = SDL_CreateWindow(
		"Cellular Automaton Sim",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth_, windowHeight_, SDL_WINDOW_SHOWN)
		) == nullptr) {
		//Log("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	primarySurface_ = SDL_GetWindowSurface(window_);

	if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
		//Log("Unable to create renderer");
		return false;
	}

	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

void CellularAutomatonApp::pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		processEvent(&event);
	}
}

void CellularAutomatonApp::processEvent(SDL_Event* event) {
}

void CellularAutomatonApp::loop() {
}

void CellularAutomatonApp::render() {
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
}

void CellularAutomatonApp::breate() {
	SDL_Delay(1);
}

void CellularAutomatonApp::cleanup() {
	if (renderer_) {
		SDL_DestroyRenderer(renderer_);
		renderer_ = nullptr;
	}
	if (window_) {
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
	SDL_Quit();
}

}
