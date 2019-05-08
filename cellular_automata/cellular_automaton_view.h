#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "cell_color_map.h"
#include "cellular_automaton.h"
#include "constants.h"
#include "type_definitions.h"

namespace cellular_automata_mvc {

class CellularAutomatonView {
public:
	CellularAutomatonView();
	~CellularAutomatonView();

	void setCellularAutomaton(
		const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton);

	void update();

	void setRenderer(SDL_Renderer* renderer);

	void reset(const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton);

	void screenshot();

private:
	void initializeTexture();

	void initializePixels();
	void updatePixels();
	void copyOldGenerations();
	void setPixelsForCurrentGeneration();

	Uint32 getPixelForCell(const cellular_automata::Cell& cell) const;

	std::string getTimestamp() const;

	static const int windowWidth_ = WINDOW_WIDTH;
	static const int windowHeight_ = WINDOW_HEIGHT;
	static const int numberOfPixels_ = WINDOW_WIDTH * WINDOW_HEIGHT;
	static const int generationLength_ = windowWidth_;

	cellular_automata::CellularAutomatonPtr automaton_;
	CellColorMap colorMap_;

	SDL_Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
	Uint32 pixels_[numberOfPixels_];
	//std::vector<Uint32> pixels_;

	static const std::string SCREENSHOT_DIR;
};

}
