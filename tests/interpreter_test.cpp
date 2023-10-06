#include <gtest/gtest.h>
#include "tokenizer.h"
#include "interpreter.h"

void testInterpreterFor(vector<token> tokens, token expectedOutput){
    tokenData data = {};
    token output = interpretFromRPN(tokens, data);
    ASSERT_EQ(output.type, expectedOutput.type);
    ASSERT_EQ(output.value, expectedOutput.value);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusOne){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 1
        },
        {
             
            .type = NUMBER,
            .value = 1
        },
        {
             
            .type = OP_PLUS,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 2});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusOne){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 2
        },
        {
             
            .type = NUMBER,
            .value = 1
        },
        {
             
            .type = OP_MINUS,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 1});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusTwoTimesFive){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 1
        },
        {
             
            .type = NUMBER,
            .value = 2
        },
        {
             
            .type = NUMBER,
            .value = 5
        },
        {
             
            .type = OP_MULTIPLY,
            .value = 0
        },
        {
             
            .type = OP_PLUS,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 11});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusFourDividedBy2){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 2
        },
        {
             
            .type = NUMBER,
            .value = 4
        },
        {
             
            .type = NUMBER,
            .value = 2
        },
        {
             
            .type = OP_DIVIDE,
            .value = 0
        },
        {
             
            .type = OP_MINUS,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 0});
}


TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultFor2ToPowerOf3){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 2
        },
        {
             
            .type = NUMBER,
            .value = 3
        },
        {
             
            .type = FUNC_POWER,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 8});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForSQRT16){
    vector<token> tokens = {
        {
             
            .type = NUMBER,
            .value = 16
        },
        {
             
            .type = FUNC_SQRT,
            .value = 0
        }
    };

    testInterpreterFor(tokens, {  .type = NUMBER, .value = 4});
}