#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class Cell
{
public:
	Cell();
	Cell(integers::state_t state);

	void setState(integers::state_t state) noexcept;
	integers::state_t getState() const noexcept;

private:
	integers::state_t _state;
};

}
