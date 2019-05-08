#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "command_line_parser.h"

using namespace cellular_automata;

namespace cellular_automata_test {

class CommandLineParserTest : public testing::Test {
protected:
	void parse(const std::string& commandLine) {
		parser_.parse(getArgsVector(commandLine));
	}

	std::vector<std::string> getArgsVector(const std::string& commandLine) const {
		std::vector<std::string> args;
		args.emplace_back("args[0]: Programname representation");
		
		std::istringstream commandLineStream(commandLine);
		std::string argument;
		while (commandLineStream >> argument)
			args.emplace_back(argument);

		return args;
	}

	CommandLineParser parser_;
};

//TEST_F(CommandLineParserTest, set_number_of_states) {
//	parse("-states 2");
//	EXPECT_EQ(parser_.getNumberOfStates(), 2);
//}

}
