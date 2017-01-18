#include "cell.h"

namespace cellular_automata
{

Cell::Cell()
	: _state(0)
{
}

Cell::Cell(integers::state_t state)
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

}
