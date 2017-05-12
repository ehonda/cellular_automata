#include "cellular_automaton_view.h"

#include <ctime>

#include <chrono>
#include <iostream>

#include "cell.h"
#include "cell_row.h"
#include "rule.h"

namespace cellular_automata_mvc {

const std::string CellularAutomatonView::SCREENSHOT_DIR = "screenshots";

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

void CellularAutomatonView::screenshot()
{
	int depth = 32;
	int pitch = windowWidth_ * sizeof(Uint32);

	SDL_Surface* pixelSurface = SDL_CreateRGBSurfaceWithFormatFrom(&pixels_, windowWidth_, windowHeight_, depth, pitch, SDL_PIXELFORMAT_ABGR8888);
	std::string name = SCREENSHOT_DIR + "/screenshot_" + getTimestamp() + "__rule_" + automaton_->getRule()->toString() + ".bmp";
	std::cout << "Screenshot taken.\n";
	SDL_SaveBMP(pixelSurface, name.c_str());
	SDL_FreeSurface(pixelSurface);
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

std::string CellularAutomatonView::getTimestamp() const
{
	auto currentTime = std::chrono::system_clock::now();
	std::time_t cTime = std::chrono::system_clock::to_time_t(currentTime);
	std::tm* timeStruct = std::localtime(&cTime);

	std::string timestamp;
	std::string UNDERSCORE("_");

	timestamp += std::to_string(timeStruct->tm_mday) + UNDERSCORE;
	timestamp += std::to_string(timeStruct->tm_mon + 1) + UNDERSCORE;
	timestamp += std::to_string(timeStruct->tm_year + 1900) + UNDERSCORE;
	timestamp += UNDERSCORE;
	timestamp += std::to_string(timeStruct->tm_hour) + UNDERSCORE;
	timestamp += std::to_string(timeStruct->tm_min) + UNDERSCORE;
	timestamp += std::to_string(timeStruct->tm_sec);

	return timestamp;
}

}
