#include <gtest/gtest.h>
#include "tokenizer.h"
#include "interpreter.h"

void testInterpreterFor(vector<token> tokens, token expectedOutput){
    token output = interpretFromRPN(tokens);
    ASSERT_EQ(output.type, expectedOutput.type);
    ASSERT_EQ(output.opType, expectedOutput.opType);
    ASSERT_EQ(output.numberVal, expectedOutput.numberVal);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForOnePlusOneMinusTwo){
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