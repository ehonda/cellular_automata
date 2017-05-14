#pragma once

#include <memory>

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

	//Needed for polymorphism when copying CellRow
	virtual std::unique_ptr<CellRowBoundaryComponent> getPtrToCopy() = 0;
	//Better version for copying
	virtual std::unique_ptr<CellRowBoundaryComponent> makeCopyFor(
		CellRow* row) = 0;
	void setCellRow(CellRow* row) noexcept;

	bool operator==(const CellRowBoundaryComponent& other) const;
	bool operator!=(const CellRowBoundaryComponent& other) const;

protected:
	virtual bool equals(const CellRowBoundaryComponent& other) const = 0;

	CellRow* row_;
};

}
