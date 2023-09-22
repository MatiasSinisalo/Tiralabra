#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "testUtilities.h"
#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;


TEST(shuntingYard_popTokensBeforeLeftParenthesis_tests, functionMovesTokensFromSourceToTargetCorrectlyWhenParentheseLeftIsLastElement){
    vector<token> output;
    vector<token> operators = {
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT
        },
        {
            .type = OPERATOR,
            .opType = PLUS
        },
        {
            .type = OPERATOR,
            .opType = MINUS
        },
    };

    popTokensBeforeLeftParenthesis(output, operators);

    vector<token> expectedOutput = {
        {
            .type = OPERATOR,
            .opType = MINUS
        },
        {
            .type = OPERATOR,
            .opType = PLUS
        },
    };
    ASSERT_EQ(operators.size(), 0);
    checkTokensMatch(output, expectedOutput);
}

TEST(shuntingYard_popTokensBeforeLeftParenthesis_tests, functionMovesTokensFromSourceToTargetCorrectlyWhenParentheseLeftIsNotLastElement){
    vector<token> output;
    vector<token> operators = {
        {
           
            .type = OPERATOR,
            .opType = MULTIPLY
            
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT
        },
        {
            .type = OPERATOR,
            .opType = PLUS
        },
        {
            .type = OPERATOR,
            .opType = MINUS
        },
    };

    popTokensBeforeLeftParenthesis(output, operators);

    vector<token> expectedOutput = {
        {
            .type = OPERATOR,
            .opType = MINUS
        },
        {
            .type = OPERATOR,
            .opType = PLUS
        },
    };
    checkTokensMatch(output, expectedOutput);

    vector<token> expectedOperators = {
        {
            .type = OPERATOR,
            .opType = MULTIPLY
        },
    };
     checkTokensMatch(operators, expectedOperators);
}



