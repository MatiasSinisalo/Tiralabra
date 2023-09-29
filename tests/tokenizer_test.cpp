#include <gtest/gtest.h>
#include "tokenizer.h"
TEST(tokenizerTests, tokenizerDetectsNumbers) {
	string input = "1";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = NUMBER,
		.numberVal = 1
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsPlusOperator){
	string input = "+";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_PLUS,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};


TEST(tokenizerTests, tokenizerDetectsMinusOperator){
	string input = "-";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_MINUS,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};


TEST(tokenizerTests, tokenizerDetectsMultiplyOperator){
	string input = "*";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_MULTIPLY,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsDivideOperator){
	string input = "/";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_DIVIDE,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsLeftParenthesesOperator){
	string input = "(";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = PARENTHESE_LEFT,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsPOWERFunction){
	string input = "POWER";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = FUNC_POWER,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerDetectsComma){
	string input = ",";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = COMMA,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};



TEST(tokenizerTests, tokenizerDetectsRightParenthesesOperator){
	string input = ")";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = PARENTHESE_RIGHT,
		.numberVal = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].numberVal, expectedToken.numberVal);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokenListForIncorrectInput){
	string input = "ThisIsAnUnkownTokenThatWillNeverExist";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokenListForIncorrectInput_2){
	string input = "1+ThisIsAnUnkownTokenThatWillNeverExist+5";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 0);
};


TEST(tokenizerTests, tokenizerDetectsNumbersAndOperators){
	string input = "1+2-3*4/5";
	vector<token> tokens = getTokensFromInputString(input);
	EXPECT_EQ(tokens.size(), 9);


	vector<token> expectedTokens = {
		{
			 
			.type = NUMBER,
			.numberVal = 1
		},
		{
			 
			.type = OP_PLUS,
			.numberVal = 0
		},
		{
			 
			.type = NUMBER,
			.numberVal = 2
		},
		{
			 
			.type = OP_MINUS,
			.numberVal = 0
		},
		{
			 
			.type = NUMBER,
			.numberVal = 3
		},
		{
			 
			.type = OP_MULTIPLY,
			.numberVal = 0
		},
		{
			 
			.type = NUMBER,
			.numberVal = 4
		},
		{
			 
			.type = OP_DIVIDE,
			.numberVal = 0
		},
		{
			 
			.type = NUMBER,
			.numberVal = 5
		}
	};
	
	for(int i = 0; i < tokens.size(); i++){
		EXPECT_EQ(tokens[i].type, expectedTokens[i].type);
		EXPECT_EQ(tokens[i].type, expectedTokens[i].type);
		EXPECT_EQ(tokens[i].numberVal, expectedTokens[i].numberVal);
	}
	
};

TEST(tokenizerTests_extractNonNumberToken, extractNonNumberTokenReturnsTokenOfTypeNONEIfExpectedTokenIsNumber){
	int pos = 0;
	token returnVal = extractNonNumberToken("", pos, NUMBER);
	EXPECT_EQ(returnVal.type, NONE);
}

TEST(tokenizerTests_extractNonNumberToken, extractNonNumberTokenReturnsTokenOfTypeNONEIfExpectedTokenIsNotFound){
	int pos = 0;
	token returnVal = extractNonNumberToken("+", pos, OP_MINUS);
	EXPECT_EQ(returnVal.type, NONE);
}


TEST(tokenizerTests_extractNumberToken, extractNumberTokenReturnsTokenOfTypeNONEIfNumberIsNotFound){
	int pos = 0;
	token returnValue = extractNumberToken("POWER", pos);
	EXPECT_EQ(returnValue.type, NONE);
}


TEST(tokenizerTests_findExpectedTokenType, returnsTokenOfTypeNONEIfNoExpectedTokenIsFound){
	const char c = 'b';
	tokenType returnVal = findExpectedTokenType(c);
	EXPECT_EQ(returnVal, NONE);
}
