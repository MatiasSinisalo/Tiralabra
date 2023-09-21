#include <gtest/gtest.h>
#include "tokenizer.h"
#include "interpreter.h"

void testInterpreterFor(vector<token> tokens, token expectedOutput){
    token output = interpretFromRPN(tokens);
    ASSERT_EQ(output.type, expectedOutput.type);
    ASSERT_EQ(output.opType, expectedOutput.opType);
    ASSERT_EQ(output.numberVal, expectedOutput.numberVal);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusOne){
    vector<token> tokens = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {.type = NUMBER, .opType = NONE, .numberVal = 2});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusOne){
    vector<token> tokens = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1
        },
        {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {.type = NUMBER, .opType = NONE, .numberVal = 1});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusTwoTimesFive){
    vector<token> tokens = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 1
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 5
        },
        {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0
        },
        {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {.type = NUMBER, .opType = NONE, .numberVal = 11});
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForTwoMinusFourDividedBy2){
    vector<token> tokens = {
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 4
        },
        {
            .type = NUMBER,
            .opType = NONE,
            .numberVal = 2
        },
        {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0
        },
        {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0
        }
    };

    testInterpreterFor(tokens, {.type = NUMBER, .opType = NONE, .numberVal = 0});
}