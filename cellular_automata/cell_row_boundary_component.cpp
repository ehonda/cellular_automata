#include "cell_row_boundary_component.h"

namespace cellular_automata {

CellRowBoundaryComponent::CellRowBoundaryComponent(CellRow* row)
	: row_(row) {
}

void CellRowBoundaryComponent::setCellRow(CellRow * row) noexcept {
	row_ = row;
}

bool CellRowBoundaryComponent::operator==(const CellRowBoundaryComponent& other) const {
	return equals(other) && other.equals(*this);
}

bool CellRowBoundaryComponent::operator!=(const CellRowBoundaryComponent & other) const
{
	return !operator==(other);
}

}
