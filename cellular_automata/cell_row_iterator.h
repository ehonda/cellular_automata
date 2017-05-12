#pragma once

#include <iterator>

#include "type_definitions.h"

namespace cellular_automata {

class CellRowIterator : public std::iterator<
	std::bidirectional_iterator_tag,
	Cell,
	std::ptrdiff_t,
	const Cell*,
	Cell> {
};

class BoundedCellRowIterator : public CellRowIterator {
public:
	explicit BoundedCellRowIterator(
		const BoundedCellRow& row,
		const CellVector::iterator& pos);

	BoundedCellRowIterator& operator++();
	BoundedCellRowIterator operator++(int);
	BoundedCellRowIterator& operator--();

	bool operator==(const BoundedCellRowIterator& other) const;
	bool operator!=(const BoundedCellRowIterator& other) const;
	reference operator*() const;

private:
	bool isOutsideBounds() const;

	const BoundedCellRow& row_;
	CellVector::iterator posInCellVector_;
	int distanceFromCellVectorEnd_ = -1;
	int distanceFromCellVectorBegin_ = 0;
};

}
