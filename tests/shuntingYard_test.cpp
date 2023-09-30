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
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
           
            .type = OP_MINUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
           .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
           .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_MINUS,
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
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
           .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
       {
            
            .type = NUMBER,
            .numberVal = 3,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = OP_PLUS,
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
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
        {
            
            .type = OP_DIVIDE,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_DIVIDE,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 4,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
    };
    
    vector<token> output = shuntingYard(input);

    checkTokensMatch(output, expected_output);
}

TEST(shuntingYardTests_shuntingYard, producesExpectedOutputForPARENTHESE_LEFT_OnePlusOne_PARENTHESE_RIGHTMultipliedByTwo){
    vector<token> input = {
        {
            
            .type  = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
          {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_MULTIPLY,
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
            
            .type  = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 9,
        },
        {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            
            .type = OP_DIVIDE,
            .numberVal = 0,
        },
        {
            
            .type  = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            
            .type  = PARENTHESE_LEFT,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
         {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
         {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type  = PARENTHESE_RIGHT,
            .numberVal = 1,
        },
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 9,
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
        },
         {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
         {
            
            .type = NUMBER,
            .numberVal = 1,
        },
         {
            
            .type = OP_PLUS,
            .numberVal = 0,
        },
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = OP_MULTIPLY,
            .numberVal = 0,
        },
        {
            
            .type = OP_DIVIDE,
            .numberVal = 0,
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
            .numberVal = 2,
        },
        {
           
            .type = COMMA,
            
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
        },
        {
            .type = PARENTHESE_RIGHT
        }
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 2,
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
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
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
           
            .type = COMMA,
          
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
        },
        {
            .type = PARENTHESE_RIGHT
        }
    };

    vector<token> expected_output = {
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = NUMBER,
            .numberVal = 1,
        },
        {
            
            .type = OP_PLUS,
        
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
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
            .numberVal = 2,
        },
        {
           
            .type = COMMA,
          
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
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
            .numberVal = 2,
        },
        {
            
            .type = NUMBER,
            .numberVal = 3,
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
