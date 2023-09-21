#include "testUtilities.h"

void checkFirstTokenIsCorrectOperator(vector<token> tokens, operatorType expectedOperatorType, int expectedSize){
    EXPECT_EQ(tokens.size(), expectedSize);
    EXPECT_EQ(tokens[tokens.size() - 1].type, OPERATOR);
    EXPECT_EQ(tokens[tokens.size() - 1].opType, expectedOperatorType);
}

void checkOperatorsAreCorrect(vector<token> tokens, vector<operatorType> expectedOperators){
    EXPECT_EQ(tokens.size(), expectedOperators.size());
    for(int i = 0; i < tokens.size(); i++){
        EXPECT_EQ(tokens[i].type, OPERATOR);
        EXPECT_EQ(tokens[i].opType, expectedOperators[i]);
    }
}

void checkTokensMatch(vector<token> tokensA, vector<token> tokensB){
    EXPECT_EQ(tokensA.size(), tokensB.size());
    for(int i = 0; i < tokensA.size(); i++){
        EXPECT_EQ(tokensA[i].type, tokensB[i].type);
        EXPECT_EQ(tokensA[i].opType, tokensB[i].opType);
        EXPECT_EQ(tokensA[i].numberVal, tokensB[i].numberVal);
    }
}
