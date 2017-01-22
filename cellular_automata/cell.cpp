#include "cell.h"

namespace cellular_automata
{

Cell::Cell() noexcept
	: _state(0)
{
}

Cell::Cell(integers::state_t state) noexcept
	: _state(state)
{
}

void Cell::setState(integers::state_t state) noexcept
{
	_state = state;
}

integers::state_t Cell::getState() const noexcept
{
	return _state;
}

bool Cell::operator==(const Cell& other) const noexcept
{
	return _state == other._state;
}

}
