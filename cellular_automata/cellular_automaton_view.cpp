#include "cellular_automaton_view.h"

#include "cell.h"
#include "cell_row.h"

namespace cellular_automata_mvc {

CellularAutomatonView::~CellularAutomatonView()
{
	SDL_DestroyTexture(texture_);
}

void CellularAutomatonView::setCellularAutomaton(
	const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton)
{
	automaton_ = automaton;
}

void CellularAutomatonView::update()
{
	SDL_RenderClear(renderer_);

	updatePixels();
	SDL_UpdateTexture(texture_, NULL, &pixels_, generationLength_ * sizeof(Uint32));
	
	SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
	SDL_RenderPresent(renderer_);
}

void CellularAutomatonView::setRenderer(SDL_Renderer* renderer) {
	renderer_ = renderer;
	initializeTexture();
}

void CellularAutomatonView::reset(const std::shared_ptr<cellular_automata::CellularAutomaton>& automaton)
{
	automaton_ = automaton;
}

void CellularAutomatonView::initializeTexture()
{
	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, windowWidth_, windowHeight_);
	initializePixels();
}

void CellularAutomatonView::initializePixels()
{
	cellular_automata::Cell zero(0);
	for (size_t i = 0; i < numberOfPixels_; ++i)
		pixels_[i] = getPixelForCell(zero);
}

void CellularAutomatonView::updatePixels()
{
	copyOldGenerations();
	setPixelsForCurrentGeneration();
}

void CellularAutomatonView::copyOldGenerations()
{
	for (int i = 0; i < numberOfPixels_ - generationLength_; ++i)
		pixels_[i] = pixels_[i + generationLength_];
}

void CellularAutomatonView::setPixelsForCurrentGeneration()
{
	auto gen = automaton_->peekCurrentGeneration();
	auto genIt = gen->cbegin();
	int offset = numberOfPixels_ - generationLength_;
	for (int i = 0; i < generationLength_; ++i, ++genIt)
		pixels_[offset + i] = getPixelForCell(*genIt);
}

Uint32 CellularAutomatonView::getPixelForCell(const cellular_automata::Cell & cell) const
{
	return colorMap_.getPixelForCell(cell);
}

}
