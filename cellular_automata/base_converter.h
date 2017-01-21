#pragma once

#include <vector>

namespace cellular_automata
{
namespace integers
{

class BaseConverter
{
public:
	using BaseBRepresentation = std::vector<long>;
	static const long MIN_BASE = 2;
	static const long MIN_INTEGER = 0;

	BaseConverter(long base);

	BaseBRepresentation getBaseBRepresentationFromInteger(long integer) const;
	long getIntegerFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const;

private:
	void throwIfInvalidBase() const;
	void throwIfInvalid(long integer) const;
	void throwIfInvalid(const BaseBRepresentation& baseBRepresentation) const;

	long _base;
};

}
}
