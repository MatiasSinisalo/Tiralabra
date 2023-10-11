#include <gtest/gtest.h>
#include "tokenizer.h"
#include "testUtilities.h"
TEST(tokenizerTests, tokenizerDetectsSingleNumbers) {
	tokenData data = {};
	vector<string> inputs = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	for(string &s : inputs){

		vector<token> tokens = getTokensFromInputString(s, data);
		EXPECT_EQ(tokens.size(), 1);

		token expectedToken = {
			
			.type = NUMBER,
			.value = stoi(s)
		};

		EXPECT_EQ(tokens[0].type, expectedToken.type) << "test failed for " << s << "\n";
		EXPECT_EQ(tokens[0].type, expectedToken.type) << "test failed for " << s << "\n";
		EXPECT_EQ(tokens[0].value, expectedToken.value) << "test failed for " << s << "\n";
	}
};

TEST(tokenizerTests, tokenizerDetectsMultiDigitNumbers) {
	tokenData data = {};
	string input = "100+50";
	

	vector<token> tokens = getTokensFromInputString(input, data);
	
	vector<token> expectedTokens = {
		{
			.type = NUMBER,
			.value = 100,
		},
		{
			.type = OP_PLUS,
		},
		{
			.type = NUMBER,
			.value = 50,
		},
	};

	
	checkTokensMatch(tokens, expectedTokens);
};


TEST(tokenizerTests, tokenizerDetectsPlusOperator){
	tokenData data = {};
	string input = "+";
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_PLUS,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};


TEST(tokenizerTests, tokenizerDetectsMinusOperator){
	tokenData data = {};
	string input = "-";
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_MINUS,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};


TEST(tokenizerTests, tokenizerDetectsMultiplyOperator){
	tokenData data = {};
	string input = "*";
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_MULTIPLY,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};

TEST(tokenizerTests, tokenizerDetectsDivideOperator){
	string input = "/";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = OP_DIVIDE,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};

TEST(tokenizerTests, tokenizerDetectsParentheses){
	string input = "()";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	

	vector<token> expectedTokens = {
		 {
			.type = PARENTHESE_LEFT,
		 },
		 {
			.type = PARENTHESE_RIGHT,
		 }
	};

	checkTokensMatch(tokens, expectedTokens);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokensForIncorrectParentheses){
	string input = "((1+1)";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	ASSERT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokensForIncorrectParentheses_2){
	string input = ")(1+1)(";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	ASSERT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokensForIncorrectOperatorAndNumberOrdering){
	string input = "+1";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	ASSERT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokensForIncorrectOperatorAndNumberOrdering_2){
	string input = "1+";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	ASSERT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokensForIncorrectFunctionSyntax){
	string input = "POWER1+1";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	ASSERT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerDetectsPOWERFunction){
	string input = "POWER";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = FUNC_POWER,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};

TEST(tokenizerTests, tokenizerDetectsSQRTFunction){
	string input = "SQRT";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = FUNC_SQRT,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};

TEST(tokenizerTests, tokenizerCreatesNewTokenTypeWhenVARIABLEFunctionIsUsed){
	string input = "VARIABLE(x,10)";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	vector<token> expectedTokens = {
		{
			.type = FUNC_SET_VARIABLE
		},
		{
			.type = PARENTHESE_LEFT
		},
		{
			.type = VARIABLE,
			.value = 1
		},
		{
			.type = COMMA
		},
		{
			.type = NUMBER,
			.value = 10
		},
		{
			.type = PARENTHESE_RIGHT
		}
	};
	checkTokensMatch(tokens, expectedTokens);

	ASSERT_EQ(data.variableStringToID.size(), 1);
	ASSERT_EQ(data.variableStringToID["x"], 1);
	checkTokensMatch(data.variableExpressions[1], {{.type=NUMBER, .value=0}});
};

TEST(tokenizerTests, tokenizerDoesNotModifyVariableIfItIsDeclaredMultipleTimes){
	string input = "VARIABLE(x,10)";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	vector<token> expectedTokens = {
		{
			.type = FUNC_SET_VARIABLE
		},
		{
			.type = PARENTHESE_LEFT
		},
		{
			.type = VARIABLE,
			.value = 1
		},
		{
			.type = COMMA
		},
		{
			.type = NUMBER,
			.value = 10
		},
		{
			.type = PARENTHESE_RIGHT
		}
	};
	checkTokensMatch(tokens, expectedTokens);
	
	string SecondInput = "VARIABLE(x,20)";
	vector<token> tokensAfterDoubleDeclaration = getTokensFromInputString(SecondInput, data);
	expectedTokens[4].value = 20;
	checkTokensMatch(tokensAfterDoubleDeclaration, expectedTokens);
	
	ASSERT_EQ(data.variableStringToID.size(), 1);
	ASSERT_EQ(data.variableStringToID["x"], 1);
	checkTokensMatch(data.variableExpressions[1], {{.type=NUMBER, .value=0}});
};



TEST(tokenizerTests, tokenizerDetectsDeclaredVariablesCorrectly){
	string input = "VARIABLE(x,10)";
	tokenData data = {};
	vector<token> tokensA = getTokensFromInputString(input, data);

	string inputB = "x";
	vector<token> output = getTokensFromInputString(inputB, data);
	vector<token> expectedTokens = {
		{
			.type  = VARIABLE,
			.value = 1
		}
	};

	checkTokensMatch(output, expectedTokens);
};

TEST(tokenizerTests, tokenizerCreatesNewFunctionTokenTypeWhenFUNCTIONFunctionIsUsed) {
	string input = "FUNCTION(foo,50*5)";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	vector<token> expectedTokens = {
		{
			.type = FUNC_SET_CUSTOM_FUNCTION,
			.value = 1
		},
		{
			.type = PARENTHESE_LEFT
		},
		{
			.type = CUSTOM_FUNCTION,
			.value = 1
		},
		{
			.type = COMMA
		},
		{
			.type = NUMBER,
			.value = 50
		},
		{
			.type = OP_MULTIPLY,
		},
		{
			.type = NUMBER,
			.value = 5
		},
		{
			.type = PARENTHESE_RIGHT
		}
	};
	checkTokensMatch(tokens, expectedTokens);

	ASSERT_EQ(data.functionStringToID.size(), 1);
	ASSERT_EQ(data.functionStringToID["foo"], 1);
	checkTokensMatch(data.functionExpressions[1], {});
};

TEST(tokenizerTests, tokenizerBehavesCorrectlyWhenMultipleFUNCTIONFunctionIsUsed) {
	string firstInput = "FUNCTION(foo,50*5)";
	tokenData data = {};
	vector<token> tokensA = getTokensFromInputString(firstInput, data);

	string input = "FUNCTION(foo,1+1)";
	vector<token> tokens = getTokensFromInputString(input, data);



	vector<token> expectedTokens = {
		{
			.type = FUNC_SET_CUSTOM_FUNCTION,
			.value = 1
		},
		{
			.type = PARENTHESE_LEFT
		},
		{
			.type = CUSTOM_FUNCTION,
			.value = 1
		},
		{
			.type = COMMA
		},
		{
			.type = NUMBER,
			.value = 1
		},
		{
			.type = OP_PLUS,
		},
		{
			.type = NUMBER,
			.value = 1
		},
		{
			.type = PARENTHESE_RIGHT
		}
	};
	checkTokensMatch(tokens, expectedTokens);

	ASSERT_EQ(data.functionStringToID.size(), 1);
	ASSERT_EQ(data.functionStringToID["foo"], 1);
	checkTokensMatch(data.functionExpressions[1], {});
};



TEST(tokenizerTests, tokenizerDetectsComma){
	string input = ",";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 1);

	token expectedToken = {
		 
		.type = COMMA,
		.value = 0
	};

	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].type, expectedToken.type);
	EXPECT_EQ(tokens[0].value, expectedToken.value);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokenListForIncorrectInput){
	string input = "ThisIsAnUnkownTokenThatWillNeverExist";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 0);
};

TEST(tokenizerTests, tokenizerReturnsEmptyTokenListForIncorrectInput_2){
	string input = "1+ThisIsAnUnkownTokenThatWillNeverExist+5";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 0);
};


TEST(tokenizerTests, tokenizerDetectsNumbersAndOperators){
	string input = "1+2-3*4/5";
	tokenData data = {};
	vector<token> tokens = getTokensFromInputString(input, data);
	EXPECT_EQ(tokens.size(), 9);


	vector<token> expectedTokens = {
		{
			 
			.type = NUMBER,
			.value = 1
		},
		{
			 
			.type = OP_PLUS,
			.value = 0
		},
		{
			 
			.type = NUMBER,
			.value = 2
		},
		{
			 
			.type = OP_MINUS,
			.value = 0
		},
		{
			 
			.type = NUMBER,
			.value = 3
		},
		{
			 
			.type = OP_MULTIPLY,
			.value = 0
		},
		{
			 
			.type = NUMBER,
			.value = 4
		},
		{
			 
			.type = OP_DIVIDE,
			.value = 0
		},
		{
			 
			.type = NUMBER,
			.value = 5
		}
	};
	
	for(int i = 0; i < tokens.size(); i++){
		EXPECT_EQ(tokens[i].type, expectedTokens[i].type);
		EXPECT_EQ(tokens[i].type, expectedTokens[i].type);
		EXPECT_EQ(tokens[i].value, expectedTokens[i].value);
	}
	
};

TEST(tokenizerTests_extractNonNumberToken, extractNonNumberTokenReturnsTokenOfTypeNONEIfExpectedTokenIsNumber) {
	int pos = 0;
	tokenData data = {};
	token returnVal = extractNonNumberToken("", pos, NUMBER, data.tokenToInputString);
	EXPECT_EQ(returnVal.type, NONE);
};

TEST(tokenizerTests_extractNonNumberToken, extractNonNumberTokenReturnsTokenOfTypeNONEIfExpectedTokenIsNotFound) {
	int pos = 0;
	tokenData data = {};
	token returnVal = extractNonNumberToken("+", pos, OP_MINUS, data.tokenToInputString);
	EXPECT_EQ(returnVal.type, NONE);
};


TEST(tokenizerTests_extractNumberToken, extractNumberTokenReturnsTokenOfTypeNONEIfNumberIsNotFound) {
	int pos = 0;
	token returnValue = extractNumberToken("POWER", pos);
	EXPECT_EQ(returnValue.type, NONE);
};



