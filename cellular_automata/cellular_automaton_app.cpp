#include "cellular_automaton_app.h"

#include <cmath>

#include <chrono>
#include <iostream>
#include <random>

#include "cell_row.h"
#include "k_nearest_neighbors_rule.h"

namespace cellular_automata {

CellularAutomatonApp CellularAutomatonApp::instance_;

CellularAutomatonApp* CellularAutomatonApp::getInstance() {
	return &instance_;
}

int CellularAutomatonApp::execute(int argc, char* argv[]) {
	return run();
}

constexpr int CellularAutomatonApp::getWindowWidth() noexcept
{
	return WINDOW_WIDTH;
}

constexpr int CellularAutomatonApp::getWindowHeight() noexcept
{
	return WINDOW_HEIGHT;
}

void CellularAutomatonApp::setInitialGeneration(const CellVector& cells)
{
	initialGeneration_ = cells;
}

void CellularAutomatonApp::setRandomInitialGeneration(size_t numberOfStates)
{
	unsigned seed = static_cast<unsigned>(
		std::chrono::system_clock::now().time_since_epoch().count());
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(0, numberOfStates - 1);

	initialGeneration_.clear();
	for (int i = 0; i < WINDOW_WIDTH; ++i)
		initialGeneration_.emplace_back(dist(gen));
}

void CellularAutomatonApp::setRule(const KNearestNeighborsRulePtr & rule)
{
	rule_ = rule;
}

void CellularAutomatonApp::setRandomKNNRule(size_t numberOfStates, size_t numberOfNeighbors)
{
	unsigned seed = static_cast<unsigned>(
		std::chrono::system_clock::now().time_since_epoch().count());
	std::mt19937 gen(seed);

	long double longStates = static_cast<long double>(numberOfStates);
	long double longNeighbors = static_cast<long double>(numberOfNeighbors);
	long long numberOfAutomata = static_cast<long long>(pow(longStates, pow(longStates, longNeighbors)));
	
	long upperBound = 0;
	if (numberOfAutomata > LONG_MAX || numberOfAutomata < 0LL)
		upperBound = LONG_MAX;
	else
		upperBound = static_cast<long>(numberOfAutomata);

	std::uniform_int_distribution<long> dist(0, upperBound);

	auto integerRep = dist(gen);
	std::cout << "#" << (ruleCounter++) << ": " << integerRep << "\n";
	rule_ = KNearestNeighborsRule::createPtr(
		integers::BaseBInteger(numberOfStates, integerRep),
		numberOfNeighbors);
}

CellularAutomatonApp::CellularAutomatonApp()
{
	setInitialGenToStandard();
}

void CellularAutomatonApp::setInitialGenToStandard()
{
	initialGeneration_ = CellVector(WINDOW_WIDTH, 0);
	initialGeneration_[WINDOW_WIDTH / 2] = 1;
}

void CellularAutomatonApp::randomReset()
{
	auto currentGen = controller_.getCellularAutomaton()->peekCurrentGeneration();
	setRandomKNNRule(rule_->getNumberOfStates(), rule_->getNumberOfNeighbors());
	
	CellVector cells;
	for (const auto& cell : *currentGen)
		cells.emplace_back(cell);
	setInitialGeneration(cells);

	controller_ = cellular_automata_mvc::CellularAutomataController(rule_, cells);
	view_.reset(controller_.getCellularAutomaton());
}

int CellularAutomatonApp::run()
{
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
	if (!initVideoAndHint())
		return false;

	if (!initWindowAndSurface())
		return false;

	if (!initRenderer())
		return false;

	initController();
	initView();

	return true;
}

bool CellularAutomatonApp::initVideoAndHint()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//Log("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		//Log("Unable to Init hinting: %s", SDL_GetError());
	}
	return true;
}

bool CellularAutomatonApp::initWindowAndSurface()
{
	if ((window_ = SDL_CreateWindow(
		"Cellular Automaton Sim",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
		) == nullptr) {
		//Log("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}
	primarySurface_ = SDL_GetWindowSurface(window_);
	return true;
}

bool CellularAutomatonApp::initRenderer()
{
	if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
		//Log("Unable to create renderer");
		return false;
	}
	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
	return true;
}

void CellularAutomatonApp::initController()
{
	controller_ = cellular_automata_mvc::CellularAutomataController(rule_, initialGeneration_);
}

void CellularAutomatonApp::initView()
{
	view_.setCellularAutomaton(controller_.getCellularAutomaton());
	view_.setRenderer(renderer_);
}

void CellularAutomatonApp::pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		processEvent(&event);
	}
}

void CellularAutomatonApp::processEvent(SDL_Event* event) {
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_p:
			view_.screenshot();
			break;
		case SDLK_r:
			randomReset();
			break;
		case SDLK_ESCAPE:
			running_ = false;
			break;
		}
	}
}

void CellularAutomatonApp::loop() {
	controller_.iterate();
}

void CellularAutomatonApp::render() {
	view_.update();
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
