#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class Cell
{
public:
	Cell() noexcept;
	Cell(integers::state_t state) noexcept;

	void setState(integers::state_t state) noexcept;
	integers::state_t getState() const noexcept;

	bool operator==(const Cell& other) const noexcept;

private:
	integers::state_t _state;
};

}
