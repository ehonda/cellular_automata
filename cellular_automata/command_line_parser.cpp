#include "command_line_parser.h"

namespace cellular_automata {

integers::state_t CommandLineParser::getNumberOfStates() const noexcept {
	return numberOfStates_;
}

integers::neighbor_t CommandLineParser::getNumberOfNeighbors() const noexcept {
	return numberOfNeighbors_;
}

void CommandLineParser::parse(const std::vector<std::string>& arguments) {
	for (currentArgument_ = arguments.cbegin(); currentArgument_ != arguments.cend(); ++currentArgument_)
		parseCurrentArgument();
}

void CommandLineParser::parseCurrentArgument() {
	//if(currentArgumentIsOption())

}

bool CommandLineParser::currentArgumentIsOption() const {
	return currentArgument_->size() > 0 && currentArgument_->at(0) == '-';
}

void CommandLineParser::parseCurrentArgumentAsOption() {
	//if(*currentArgument_ == "-states")

}

void CommandLineParser::setNumberOfStates(integers::state_t numberOfStates) {
	numberOfStates_ = numberOfStates;
}



}
