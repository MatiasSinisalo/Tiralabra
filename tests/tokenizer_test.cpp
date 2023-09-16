#include <gtest/gtest.h>
#include "tokenizer.h"
TEST(tokenizerTests, tokenizerDetectsNumbers) {
	string input = "1";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.tokenType = NUMBER,
		.opType = NONE,
		.numberVal = 1
	};

	EXPECT_EQ(tokens[0].tokenType, expectedToken.tokenType);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};