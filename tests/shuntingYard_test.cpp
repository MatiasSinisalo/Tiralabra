#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "testUtilities.h"
#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;


TEST(shuntingYardTests_shuntingYard, producesExpectedOutputFor1Plus1Minus2){
    vector<token> input = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
    };

    vector<token> expected_output = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForOnePlus2Plus3Times4){
    vector<token> input = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 3,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
    };

    vector<token> expected_output = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
       {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 3,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForOnePlusFourDividedByTwoMultipliedByFour){
    vector<token> input = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
        {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
    };

    vector<token> expected_output = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForPARENTHESE_LEFT_OnePlusOne_PARENTHESE_RIGHTMultipliedByTwo){
    vector<token> input = {
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
    };

    vector<token> expected_output = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
          {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

//this tests for (9+3)/((1+1)*2)
//in RPN it should be: 93+11+2*/
TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForMultipleParentheses){
    vector<token> input = {
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 9,
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 3,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
         {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
         {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
    };

    vector<token> expected_output = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 9,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 3,
        },
         {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
         {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1,
        },
         {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0,
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2,
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0,
        },
        {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}