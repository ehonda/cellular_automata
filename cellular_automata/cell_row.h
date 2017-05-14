#pragma once

#include <memory>

#include "cell_row_boundary_component.h"
#include "type_definitions.h"

namespace cellular_automata {

class CellRow {
public:
	CellRow() = default;
	CellRow(const CellVector& cells, const RulePtr& rule);
	//Obsolete
	CellRow(const RulePtr& rule);
	//Obsolete
	CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr);
	CellRow(const CellRow& other);
	virtual ~CellRow() = default;

	CellNeighborhoodPtr getNeighborhood(const CellVector::const_iterator& center) const;
	virtual CellVector getCellNeighborhood(const CellVector::const_iterator& center) const;
	
	RulePtr getRule() const;
	void setBoundaryComponent(std::unique_ptr<CellRowBoundaryComponent>&& boundaryComponent);
	const std::unique_ptr<CellRowBoundaryComponent>& getBoundaryComponent() const noexcept;

	CellVector::iterator begin() noexcept;
	CellVector::iterator end() noexcept;
	CellVector::const_iterator cbegin() const noexcept;
	CellVector::const_iterator cend() const noexcept;

	//Obsolete, CellRow will not be used polymorphically anymore
	CellRowPtr getPtrToCopy() const;
	//Operator= replaces old uses of getPtrToCopy() since ptrs to CellRows
	//are not needed anymore
	CellRow& operator=(const CellRow& other);

	bool operator==(const CellRow& other) const;
	bool operator!=(const CellRow& other) const;

private:
	void throwIfCellNeighborhoodCreatorIsNullPtr() const;

	virtual CellNeighborhoodPtr doGetNeighborhood(const CellVector::const_iterator& center) const;
	virtual CellVector::iterator doBegin() noexcept;
	virtual CellVector::iterator doEnd() noexcept;
	virtual CellVector::const_iterator doCbegin() const noexcept;
	virtual CellVector::const_iterator doCend() const noexcept;
	virtual CellRowPtr doGetPtrToCopy() const;

protected:
	virtual bool equals(const CellRow& other) const;

	RulePtr rule_;
	CellVector cells_;
	std::unique_ptr<CellRowBoundaryComponent> boundaryComponent_;
	CellNeighborhoodCreatorPtr cellNeighborhoodCreator_;
};

}
