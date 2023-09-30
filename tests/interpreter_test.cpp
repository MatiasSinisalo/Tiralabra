#include <gtest/gtest.h>
#include "tokenizer.h"
#include "interpreter.h"

void testInterpreterFor(vector<token> tokens, token expectedOutput){
    token output = interpretFromRPN(tokens);
    ASSERT_EQ(output.type, expectedOutput.type);
    ASSERT_EQ(output.numberVal, expectedOutput.numberVal);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusOne){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 1
        },
        {
             
            .type = NUMBER,
            .numberVal = 1
        },
        {
             
            .type = OP_PLUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 2});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusOne){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 2
        },
        {
             
            .type = NUMBER,
            .numberVal = 1
        },
        {
             
            .type = OP_MINUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 1});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusTwoTimesFive){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 1
        },
        {
             
            .type = NUMBER,
            .numberVal = 2
        },
        {
             
            .type = NUMBER,
            .numberVal = 5
        },
        {
             
            .type = OP_MULTIPLY,
            .numberVal = 0
        },
        {
             
            .type = OP_PLUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 11});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusFourDividedBy2){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 2
        },
        {
             
            .type = NUMBER,
            .numberVal = 4
        },
        {
             
            .type = NUMBER,
            .numberVal = 2
        },
        {
             
            .type = OP_DIVIDE,
            .numberVal = 0
        },
        {
             
            .type = OP_MINUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 0});
}


TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultFor2ToPowerOf3){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 2
        },
        {
             
            .type = NUMBER,
            .numberVal = 3
        },
        {
             
            .type = FUNC_POWER,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 8});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForSQRT16){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .numberVal = 16
        },
        {
             
            .type = FUNC_SQRT,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .numberVal = 4});
}