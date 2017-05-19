#pragma once

#include <memory>

#include "cell_neighborhood_creator.h"
#include "cell_row_boundary_component.h"
#include "type_definitions.h"

namespace cellular_automata {

class CellRow {
public:
	CellRow() = default;
	CellRow(const CellVector& cells, const RulePtr& rule);
	CellRow(const CellRow& other);

	CellVector getCellNeighborhood(const CellVector::const_iterator& center) const;
	
	RulePtr getRule() const;
	void setBoundaryComponent(std::unique_ptr<CellRowBoundaryComponent>&& boundaryComponent);
	const std::unique_ptr<CellRowBoundaryComponent>& getBoundaryComponent() const noexcept;

	CellVector::iterator begin() noexcept;
	CellVector::iterator end() noexcept;
	CellVector::const_iterator cbegin() const noexcept;
	CellVector::const_iterator cend() const noexcept;

	CellRow& operator=(const CellRow& other);

	bool operator==(const CellRow& other) const;
	bool operator!=(const CellRow& other) const;

private:
	void throwIfCellNeighborhoodCreatorIsNullPtr() const;

	CellVector cells_;
	std::unique_ptr<CellRowBoundaryComponent> boundaryComponent_;
	CellNeighborhoodCreatorPtr cellNeighborhoodCreator_;
};

}
