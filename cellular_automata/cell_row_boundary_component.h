#pragma once

#include "cell.h"

//Begin forward declarations
namespace cellular_automata {
class CellRow;
}
//End forward declarrations

namespace cellular_automata {

class CellRowBoundaryComponent {
public:
	CellRowBoundaryComponent() = default;
	CellRowBoundaryComponent(CellRow* row);

	virtual Cell getCellBeforeFirstCellInRow(
		size_t distanceToFirst) = 0;
	virtual Cell getCellBeyondLastCellInRow(
		size_t distanceToLast) = 0;

private:
	CellRow* row_;
};

}
