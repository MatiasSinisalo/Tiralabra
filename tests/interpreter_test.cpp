#include <gtest/gtest.h>
#include "testUtilities.h"
#include "tokenizer.h"
#include "interpreter.h"

void testInterpreterFor(vector<token> tokens, token expectedOutput){
    tokenData data = {};
    token output = interpretFromRPN(tokens, data);
    ASSERT_EQ(output.type, expectedOutput.type);
    ASSERT_EQ(output.value, expectedOutput.value);
}

void testInterpreterFor(vector<token> tokens, token expectedOutput,  tokenData &data){
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

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultFor_SetVariable_x_10){
    tokenData data = {

        .variableStringToID = {{"x", 1}},
        .variableExpressions = {
                {1, 
                    {{.type = NUMBER, .value=0}}
                }
            }
    };
    
    vector<token> inputTokens = {
        {
            .type = VARIABLE,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 10 
        },
        {
            .type = FUNC_SET_VARIABLE
        }
    };

    testInterpreterFor(inputTokens, {  .type = NUMBER, .value = 10}, data);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForMultipleSetVariables){
    tokenData data = {

        .variableStringToID = {{"x", 1}},
        .variableExpressions = {
                {1, 
                    {{.type = NUMBER, .value=0}}
                }
            }
    };
    
    vector<token> inputTokens = {
        {
            .type = VARIABLE,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 10 
        },
        {
            .type = FUNC_SET_VARIABLE
        }
    };
    testInterpreterFor(inputTokens, {  .type = NUMBER, .value = 10}, data);
    ASSERT_EQ(data.variableExpressions[1][0].value, 10);

    vector<token> secondInputTokens = {
        {
            .type = VARIABLE,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 100 
        },
        {
            .type = FUNC_SET_VARIABLE
        }
    };
    testInterpreterFor(secondInputTokens, {  .type = NUMBER, .value = 100}, data);

    ASSERT_EQ(data.variableExpressions[1][0].value, 100);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForDeclaredVariables){
    tokenData data = {

        .variableStringToID = {{"x", 1}},
        .variableExpressions = {
                {1, 
                    {{.type = NUMBER, .value=100}}
                }
            }
    };
    
    vector<token> inputTokens = {
        {
            .type = VARIABLE,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 10 
        },
        {
            .type = OP_PLUS
        }
    };

    testInterpreterFor(inputTokens, {  .type = NUMBER, .value = 110}, data);
}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForSET_FUNCTION) {
    tokenData data = {

        .functionStringToID = {{"foo", 1}},
        .functionExpressions = {
                {1,
                    {}
                }
            }
    };

    vector<token> inputTokens = {
        {
            .type = CUSTOM_FUNCTION,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_PLUS
        },
        {
            .type = FUNC_SET_CUSTOM_FUNCTION,
            .value = 1
        }
    };

    testInterpreterFor(inputTokens, { .type = NUMBER, .value = 2}, data);

    ASSERT_EQ(data.functionStringToID.size(), 1);
    ASSERT_EQ(data.functionStringToID["foo"], 1);
    checkTokensMatch(data.functionExpressions[1], {
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_PLUS
        } });

}


TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForMultipleSET_FUNCTIONOnTheSameFunction) {
    tokenData data = {

        .functionStringToID = {{"foo", 1}},
        .functionExpressions = {
                {1,
                    {}
                }
            }
    };

    vector<token> firstInputTokens = {
        {
            .type = CUSTOM_FUNCTION,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_PLUS
        },
        {
            .type = FUNC_SET_CUSTOM_FUNCTION,
            .value = 1
        }
    };

    testInterpreterFor(firstInputTokens, { .type = NUMBER, .value = 2 }, data);


    vector<token> secondInputTokens = {
        {
            .type = CUSTOM_FUNCTION,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 5
        },
        {
            .type = NUMBER,
            .value = 5
        },
        {
            .type = OP_MULTIPLY
        },
        {
            .type = FUNC_SET_CUSTOM_FUNCTION,
            .value = 1
        }
    };
    testInterpreterFor(firstInputTokens, { .type = NONE, .value = 0 }, data);

    ASSERT_EQ(data.functionStringToID.size(), 1);
    ASSERT_EQ(data.functionStringToID["foo"], 1);
    checkTokensMatch(data.functionExpressions[1], {
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_PLUS
        } });

}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForCustomFunction) {
    tokenData data = {

        .functionStringToID = {{"foo", 1}},
        .functionExpressions = {
            {1,
                {
                    {
                        .type = NUMBER,
                        .value = 1
                    },
                    {
                        .type = NUMBER,
                        .value = 1
                    },
                    {
                        .type = OP_MINUS
                    }
                }
            }
        }
    };

    vector<token> inputTokens = {
        {
            .type = CUSTOM_FUNCTION,
            .value = 1
        },
    };

    testInterpreterFor(inputTokens, { .type = NUMBER, .value = 0 }, data);

    ASSERT_EQ(data.functionStringToID.size(), 1);
    ASSERT_EQ(data.functionStringToID["foo"], 1);
    checkTokensMatch(data.functionExpressions[1], {
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_MINUS
        } });

}

TEST(InterpreterTests, interpretFromRPNReturnsCorrectResultForMultipleDifferentCustomFunctions) {
    tokenData data = {

        .functionStringToID = {{"foo", 1}, {"bar", 2}},
        .functionExpressions = {
        {1,
            {
                {
                    .type = NUMBER,
                    .value = 1
                },
                {
                    .type = NUMBER,
                    .value = 1
                },
                {
                    .type = OP_PLUS
                }
            }
        },
        {2,
                {
                    {
                        .type = NUMBER,
                        .value = 2
                    },
                    {
                        .type = NUMBER,
                        .value = 3
                    },
                    {
                        .type = OP_PLUS
                    }
                }
            }
        }
    };

    vector<token> inputTokens = {
        {
            .type = CUSTOM_FUNCTION,
            .value = 1
        },
        {
            .type = CUSTOM_FUNCTION,
            .value = 2
        },
        {
            .type = OP_MULTIPLY
        }
    };

    testInterpreterFor(inputTokens, { .type = NUMBER, .value = 10 }, data);

    ASSERT_EQ(data.functionStringToID.size(), 2);

    ASSERT_EQ(data.functionStringToID["foo"], 1);
    checkTokensMatch(data.functionExpressions[1], {
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = NUMBER,
            .value = 1
        },
        {
            .type = OP_PLUS
        } });
    

    ASSERT_EQ(data.functionStringToID["bar"], 2);
    checkTokensMatch(data.functionExpressions[2], {
       {
           .type = NUMBER,
           .value = 2
       },
       {
           .type = NUMBER,
           .value = 3
       },
       {
           .type = OP_PLUS
       } });

}


