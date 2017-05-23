#pragma once

#include <cctype>

#include <stdexcept>
#include <string>

#include "base_converter.h"

using namespace cellular_automata;
using namespace integers;

namespace cellular_automata_test {

inline BaseConverter::BaseBRepresentation
convertToLittleEndian(const std::string& bigEndianRep) {
	BaseConverter::BaseBRepresentation littleEndianRep;
	for (auto digitIt = bigEndianRep.rbegin(); digitIt != bigEndianRep.rend(); ++digitIt) {
		if (!isdigit(*digitIt))
			throw std::invalid_argument("Big endian representation could not be parsed as as integer from string.");
		else
			littleEndianRep.emplace_back(*digitIt - '0');
	}
	return littleEndianRep;
}

}
