#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "testUtilities.h"
#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;





TEST(shuntingYardTests_followCountingRules, PlusPlusCausesPlusToEnterOutput){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, {.type = OP_PLUS});
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, OP_PLUS, 1);

    
    followCountingRules(output, operators, { .type = OP_PLUS });
    checkFirstTokenIsCorrectOperator(output, OP_PLUS, 1);
    checkFirstTokenIsCorrectOperator(operators, OP_PLUS, 1);
}



TEST(shuntingYardTests_followCountingRules, PlusMinusCausesPlusToEnterOutput){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, { .type = OP_PLUS });
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, OP_PLUS, 1);
    
    followCountingRules(output, operators, { .type = OP_MINUS });
    checkFirstTokenIsCorrectOperator(output, OP_PLUS, 1);
    checkFirstTokenIsCorrectOperator(operators, OP_MINUS, 1);
}

TEST(shuntingYardTests_followCountingRules, plusMultiplyStaysOnOperators){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, { .type = OP_PLUS });
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, OP_PLUS, 1);
    
    followCountingRules(output, operators, { .type = OP_MULTIPLY });
    EXPECT_EQ(output.size(), 0);
    
    checkOperatorsAreCorrect(operators, {OP_PLUS, OP_MULTIPLY});
}

TEST(shuntingYardTests_followCountingRules, multiplyPlusCausesMultiplyToEnterOutput){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, { .type = OP_MULTIPLY });
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, OP_MULTIPLY, 1);
    
    followCountingRules(output, operators, { .type = OP_PLUS });
    checkOperatorsAreCorrect(output, {OP_MULTIPLY});
    checkOperatorsAreCorrect(operators, {OP_PLUS});
}