#include "RPN.h"
#include <gtest.h>
#include <sstream>

TEST(RPN, correct_calculation_add)
{
	stringstream ss;
	ss << "1+1";
	string input;
	ss >> input;
	double res = RPN::Calculate(input);
	EXPECT_EQ(2, res);
}