#pragma once

#include <string>
#include <vector>

namespace cellular_automata
{
namespace integers
{

class BaseBInteger
{
public:
	typedef typename std::vector<long> BaseBRepresentation;

	BaseBInteger() = default;
	BaseBInteger(long base, long integer);
	BaseBInteger(long base, const BaseBRepresentation& baseBRepresentation);

	long getInteger() const noexcept;
	const BaseBRepresentation& getBaseBRepresentation() const noexcept;
	long getDigitAt(size_t index) const;

	long getBase() const noexcept;

	bool operator==(const BaseBInteger& other) const noexcept;

private:
	long _base;
	long _integer;
	BaseBRepresentation _baseBRepresentation;
};

}
}
