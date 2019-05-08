#pragma once

#include <string>
#include <vector>

#include "type_definitions.h"

namespace cellular_automata {

class CommandLineParser {
public:
	integers::state_t getNumberOfStates() const noexcept;
	integers::neighbor_t getNumberOfNeighbors() const noexcept;

	void parse(const std::vector<std::string>& arguments);

private:
	void parseCurrentArgument();

	bool currentArgumentIsOption() const;
	void parseCurrentArgumentAsOption();

	void setNumberOfStates(integers::state_t numberOfStates);

	std::vector<std::string>::const_iterator currentArgument_;

	integers::state_t numberOfStates_;
	integers::neighbor_t numberOfNeighbors_;
};

}