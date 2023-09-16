#include <gtest/gtest.h>
#include "tokenizer.h"
TEST(tokenizerTests, tokenizerDetectsNumbers) {
	string input = "1";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = NUMBER,
		.opType = NONE,
		.numberVal = 1
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};