#include "cell_row_iterator.h"

#include "bounded_cell_row.h"

namespace cellular_automata {

BoundedCellRowIterator::BoundedCellRowIterator(
	const BoundedCellRow& row, const CellVector::iterator& pos)
	: row_(row), posInCellVector_(pos)
{
}

BoundedCellRowIterator& BoundedCellRowIterator::operator++()
{
	if (posInCellVector_ == row_.cells_.end())
		++distanceFromCellVectorEnd_;
	else
		++posInCellVector_;
	return *this;
}

BoundedCellRowIterator BoundedCellRowIterator::operator++(int)
{
	auto retval = *this;
	++(*this);
	return retval;
}

BoundedCellRowIterator& BoundedCellRowIterator::operator--()
{
	return *this;
}

bool BoundedCellRowIterator::operator==(const BoundedCellRowIterator& other) const
{
	return row_ == other.row_
		&& posInCellVector_ == other.posInCellVector_;
}

bool BoundedCellRowIterator::operator!=(const BoundedCellRowIterator& other) const
{
	return !(*this == other);
}

BoundedCellRowIterator::reference BoundedCellRowIterator::operator*() const
{
	if (isOutsideBounds())
		return row_._boundaryCell;
	else
		return *posInCellVector_;
}

bool BoundedCellRowIterator::isOutsideBounds() const
{
	return distanceFromCellVectorEnd_ >= 0
		|| distanceFromCellVectorBegin_ > 0;
}

}
