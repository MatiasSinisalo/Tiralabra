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

TEST(tokenizerTests, tokenizerDetectsPlusOperator){
	string input = "+";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = PLUS,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};


TEST(tokenizerTests, tokenizerDetectsMinusOperator){
	string input = "-";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = MINUS,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};


TEST(tokenizerTests, tokenizerDetectsMultiplyOperator){
	string input = "*";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = MULTIPLY,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsDivideOperator){
	string input = "/";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = DIVIDE,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsLeftParenthesesOperator){
	string input = "(";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = PARENTHESE_LEFT,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsRightParenthesesOperator){
	string input = ")";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		.type = OPERATOR,
		.opType = PARENTHESE_RIGHT,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].opType, expectedToken.opType);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsNumbersAndOperators){
	string input = "1+2-3*4/5";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 9);


	vector<token> expectedTokens = {
		{
			.type = NUMBER,
			.opType = NONE,
			.numberVal = 1
		},
		{
			.type = OPERATOR,
			.opType = PLUS,
			.numberVal = 0
		},
		{
			.type = NUMBER,
			.opType = NONE,
			.numberVal = 2
		},
		{
			.type = OPERATOR,
			.opType = MINUS,
			.numberVal = 0
		},
		{
			.type = NUMBER,
			.opType = NONE,
			.numberVal = 3
		},
		{
			.type = OPERATOR,
			.opType = MULTIPLY,
			.numberVal = 0
		},
		{
			.type = NUMBER,
			.opType = NONE,
			.numberVal = 4
		},
		{
			.type = OPERATOR,
			.opType = DIVIDE,
			.numberVal = 0
		},
		{
			.type = NUMBER,
			.opType = NONE,
			.numberVal = 5
		}
	};
	
	for(int i = 0; i < tokens.size(); i++){
		EXPECT_EQ(tokens[i].type, expectedTokens[i].type);
		EXPECT_EQ(tokens[i].opType, expectedTokens[i].opType);
		EXPECT_EQ(tokens[i].numberVal, expectedTokens[i].numberVal);
	}
	
};

