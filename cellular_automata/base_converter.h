#pragma once

#include <vector>

namespace cellular_automata
{
namespace integers
{

class BaseConverter
{
public:
	typedef typename std::vector<long> BaseBRepresentation;

	BaseConverter(long base);

	BaseBRepresentation getBaseBRepresentationFromInteger(long integer) const;
	long getIntegerFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const;

private:
	long _base;
};

}
}