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
            
            .type = PARENTHESE_LEFT
        },
        {
           
            .type = OP_PLUS
        },
        {
         
            .type = OP_MINUS
        },
    };

    popTokensBeforeLeftParenthesis(output, operators);

    vector<token> expectedOutput = {
        {
          
            .type = OP_MINUS
        },
        {
           
            .type = OP_PLUS
        },
    };
    ASSERT_EQ(operators.size(), 0);
    checkTokensMatch(output, expectedOutput);
}

TEST(shuntingYard_popTokensBeforeLeftParenthesis_tests, functionMovesTokensFromSourceToTargetCorrectlyWhenParentheseLeftIsNotLastElement){
    vector<token> output;
    vector<token> operators = {
        {
           
            
            .type =OP_MULTIPLY
            
        },
        {
            
            .type = PARENTHESE_LEFT
        },
        {
           
            .type = OP_PLUS
        },
        {
          
            .type = OP_MINUS
        },
    };

    popTokensBeforeLeftParenthesis(output, operators);

    vector<token> expectedOutput = {
        {
          
            .type = OP_MINUS
        },
        {
            
            .type = OP_PLUS
        },
    };
    checkTokensMatch(output, expectedOutput);

    vector<token> expectedOperators = {
        {
           
            .type =OP_MULTIPLY
        },
    };
     checkTokensMatch(operators, expectedOperators);
}

TEST(shuntingYard_popTokensBeforeLeftParenthesis_tests, functionMovesTokensFromSourceToTargetCorrectlyWhenThereAreMultipleLeftParenthesis){
    vector<token> output;
    vector<token> operators = {
        {
            
            .type = PARENTHESE_LEFT
        },
        {
           
           
            .type =OP_MULTIPLY
            
        },
        {
           
            .type = PARENTHESE_LEFT
        },
        {
           
            .type = OP_PLUS
        },
        {
           
            .type = OP_MINUS
        },
    };

    popTokensBeforeLeftParenthesis(output, operators);

    vector<token> expectedOutput = {
        {
            
            .type = OP_MINUS
        },
        {
           
            .type = OP_PLUS
        },
    };
    checkTokensMatch(output, expectedOutput);

    vector<token> expectedOperators = {
        {
           
            .type = PARENTHESE_LEFT
        },
        {
          
            .type =OP_MULTIPLY
        },
    };
     checkTokensMatch(operators, expectedOperators);
}


