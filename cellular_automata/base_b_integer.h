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
	using BaseBRepresentation = std::vector<long>;
	static const long DEFAULT_BASE = 10;
	static const long DEFAULT_INTEGER = 0;
	static const BaseBRepresentation DEFAULT_BASE_B_REPRESENTATION;

	BaseBInteger();
	BaseBInteger(long base, long integer);
	BaseBInteger(long base, const BaseBRepresentation& baseBRepresentation);

	long getBase() const noexcept;
	long getInteger() const noexcept;
	const BaseBRepresentation& getBaseBRepresentation() const noexcept;
	long getDigitAt(size_t index) const noexcept;

	bool operator==(const BaseBInteger& other) const noexcept;

private:
	long _base;
	long _integer;
	BaseBRepresentation _baseBRepresentation;
};

}
}
