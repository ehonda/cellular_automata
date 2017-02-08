#include <string>

#include "gtest/gtest.h"

#include "command_line_parser.h"
#include "command_line_parser.cpp"

namespace
{

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CommandLineParserTest : public testing::Test
{

};


//-----------------------------------------------------------------------------------------------
//BEHAVIORAL TESTS

TEST_F(CommandLineParserTest, Assigned_param_rule_should_create_appropriate_rule)
{
	//Given: A user entered -rule 2 30
	std::string input = "-rule 2 30";

	//When: it is parsed by the CommandLineParser
	//CommandLineParser.parse(input);

	//Then: the parser should set the rule to: knn-3, base 2, integer 30

}

}
