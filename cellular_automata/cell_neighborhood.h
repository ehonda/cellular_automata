#pragma once

#include "base_b_integer.h"
#include "cell.h"

namespace cellular_automata
{

class CellNeighborhood
{
public:
	virtual const integers::BaseBInteger& getIntegerEncodedCellNeighborhood() const = 0;
	virtual bool operator==(const CellNeighborhood& other) const noexcept;
};

}