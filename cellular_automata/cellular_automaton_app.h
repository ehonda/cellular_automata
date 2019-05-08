#pragma once

#include <SDL.h>

#include "cellular_automata_controller.h"
#include "cellular_automaton_view.h"
#include "constants.h"
#include "type_definitions.h"

namespace cellular_automata {

class CellularAutomatonApp {
public:
	static const int WINDOW_WIDTH = cellular_automata_mvc::WINDOW_WIDTH;
	static const int WINDOW_HEIGHT = cellular_automata_mvc::WINDOW_HEIGHT;

	static CellularAutomatonApp* getInstance();

	int execute(int argc, char* argv[]);
	//int execute(const cellular_automata::KNearestNeighborsRulePtr& knnRule);

	static constexpr int getWindowWidth() noexcept;
	static constexpr int getWindowHeight() noexcept;

	void setInitialGeneration(const CellVector& cells);
	void setRandomInitialGeneration(size_t numberOfStates, std::size_t size = WINDOW_WIDTH);

	void setRule(const RulePtr& rule);
	//void setRandomKNNRule(size_t numberOfStates, size_t numberOfNeighbors);

private:
	CellularAutomatonApp();
	void setInitialGenToStandard();

	void randomReset();

	int run();
	bool init();
	bool initVideoAndHint();
	bool initWindowAndSurface();
	bool initRenderer();
	void initController();
	void initView();

	void pollEvents();
	void processEvent(SDL_Event* event);
	void loop();
	void render();
	void breathe();

	void cleanup();

	static CellularAutomatonApp instance_;
	bool running_ = false;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* primarySurface_ = nullptr;

	cellular_automata_mvc::CellularAutomataController controller_;
	cellular_automata_mvc::CellularAutomatonView view_;

	RulePtr rule_;
	CellVector initialGeneration_;
	int ruleCounter = 0;
};

}
