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
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
           
            .type = OP_MINUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
           .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
           .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_MINUS,
            .value = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForOnePlus2Plus3Times4){
    vector<token> input = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
           .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
       {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForOnePlusFourDividedByTwoMultipliedByFour){
    vector<token> input = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
        {
            
            .type = OP_DIVIDE,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_DIVIDE,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 4,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForPARENTHESE_LEFT_OnePlusOne_PARENTHESE_RIGHTMultipliedByTwo){
    vector<token> input = {
        {
            
            .type  = PARENTHESE_LEFT,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .value = 1,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
          {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
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
            
            .type  = PARENTHESE_LEFT,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 9,
        },
        {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .value = 1,
        },
        {
            
            .type = OP_DIVIDE,
            .value = 0,
        },
        {
            
            .type  = PARENTHESE_LEFT,
            .value = 1,
        },
        {
            
            .type  = PARENTHESE_LEFT,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
         {
            
            .type = OP_PLUS,
            .value = 0,
        },
         {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .value = 1,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .value = 1,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 9,
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
         {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
         {
            
            .type = NUMBER,
            .value = 1,
        },
         {
            
            .type = OP_PLUS,
            .value = 0,
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = OP_MULTIPLY,
            .value = 0,
        },
        {
            
            .type = OP_DIVIDE,
            .value = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputFOR2ToPowerOF3){
    vector<token> input = {
        {
            
            .type = FUNC_POWER,
        },
        {
            
            .type = PARENTHESE_LEFT,
           
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
           
            .type = COMMA,
            
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            .type = PARENTHESE_RIGHT
        }
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type = FUNC_POWER,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputFor_PARENTHESIS_LEFT_1PLUS1__PARENTHESIS_RIGHT_ToPowerOf3){
    vector<token> input = {
        {
            
            .type = FUNC_POWER,
            
        },
        {
            
            .type = PARENTHESE_LEFT,
          
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
           
            .type = COMMA,
          
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            .type = PARENTHESE_RIGHT
        }
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = NUMBER,
            .value = 1,
        },
        {
            
            .type = OP_PLUS,
        
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type = FUNC_POWER,
           
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}


TEST(shuntingYardTests_shuntingYard, producesExpectedOutputFor_SquareRootOf_2_toPowerOf_3){
    vector<token> input = {
        {
            
            .type = FUNC_SQRT,
            
        },
        {
            
            .type = PARENTHESE_LEFT,
          
        },
        {
            
            .type = FUNC_POWER,
        },
        {
            
            .type = PARENTHESE_LEFT,
          
        },
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
           
            .type = COMMA,
          
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            .type = PARENTHESE_RIGHT
        },
        {
            
            .type = PARENTHESE_RIGHT,
          
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .value = 2,
        },
        {
            
            .type = NUMBER,
            .value = 3,
        },
        {
            
            .type = FUNC_POWER,
        
        },
        {
            
            .type = FUNC_SQRT,
           
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputFor_FUNCTION_CUSTOM_FUNCTION_1_plus_1) {
    vector<token> input = {
        {

            .type = FUNC_SET_CUSTOM_FUNCTION,
            .value = 1,
        },
        {

            .type = PARENTHESE_LEFT,

        },
        {

            .type = CUSTOM_FUNCTION,
            .value = 1
        },
        {
            .type = COMMA,
        },
        {

            .type = NUMBER,
            .value = 1,
        },
        {

            .type = OP_PLUS,

        },
        {

            .type = NUMBER,
            .value = 1,
        },
        {
            .type = PARENTHESE_RIGHT
        },
    };

    vector<token> expected_output = {
        {

            .type = CUSTOM_FUNCTION,
            .value = 1,
        },
        {

            .type = NUMBER,
            .value = 1,
        },
        {

            .type = NUMBER,
            .value = 1,
        },
         {

            .type = OP_PLUS,

        },
        {

            .type = FUNC_SET_CUSTOM_FUNCTION,
            .value=1,

        },
    };

    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForCustomFunctionTimesFour) {
    vector<token> input = {
        {

            .type = CUSTOM_FUNCTION,
            .value = 1,
        },
        {

            .type = PARENTHESE_LEFT,

        },
        {
            .type = PARENTHESE_RIGHT
        },
        {
            .type = OP_MULTIPLY
        },
        {
            .type = NUMBER,
            .value = 4
        }
    };

    vector<token> expected_output = {
        {

            .type = CUSTOM_FUNCTION,
            .value = 1,
        },
        {

            .type = NUMBER,
            .value = 4,
        },
        {

            .type = OP_MULTIPLY,
        },
    };

    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}
