#pragma once

#include <memory>

#include <SDL.h>

#include "cell_color_map.h"
#include "cellular_automaton.h"
#include "type_definitions.h"

namespace cellular_automata_mvc {

class CellularAutomatonView {
public:
	CellularAutomatonView() = default;
	~CellularAutomatonView();

	void setCellularAutomaton(
		const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton);

	void update();

	void setRenderer(SDL_Renderer* renderer);

	void reset(const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton);

private:
	void initializeTexture();

	void initializePixels();
	void updatePixels();
	void copyOldGenerations();
	void setPixelsForCurrentGeneration();

	Uint32 getPixelForCell(const cellular_automata::Cell& cell) const;

	static const int windowWidth_ = 1024;
	static const int windowHeight_ = 768;
	static const int numberOfPixels_ = 1024 * 768;
	static const int generationLength_ = windowWidth_;

	cellular_automata::CellularAutomatonPtr automaton_;
	CellColorMap colorMap_;

	SDL_Renderer* renderer_ = nullptr;
	SDL_Texture* texture_ = nullptr;
	Uint32 pixels_[numberOfPixels_];
};

}
