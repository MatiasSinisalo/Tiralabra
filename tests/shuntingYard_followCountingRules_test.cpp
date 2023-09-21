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


    followCountingRules(output, operators, {.type = OPERATOR, .opType = PLUS, .numberVal = 0});
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, PLUS, 1);

    
    followCountingRules(output, operators, {.type = OPERATOR, .opType = PLUS, .numberVal = 0});
    checkFirstTokenIsCorrectOperator(output, PLUS, 1);
    checkFirstTokenIsCorrectOperator(operators, PLUS, 1);
}



TEST(shuntingYardTests_followCountingRules, PlusMinusCausesPlusToEnterOutput){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, {.type = OPERATOR, .opType = PLUS, .numberVal = 0});
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, PLUS, 1);
    
    followCountingRules(output, operators, {.type = OPERATOR, .opType = MINUS, .numberVal = 0});
    checkFirstTokenIsCorrectOperator(output, PLUS, 1);
    checkFirstTokenIsCorrectOperator(operators, MINUS, 1);
}

TEST(shuntingYardTests_followCountingRules, plusMultiplyStaysOnOperators){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, {.type = OPERATOR, .opType = PLUS, .numberVal = 0});
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, PLUS, 1);
    
    followCountingRules(output, operators, {.type = OPERATOR, .opType = MULTIPLY, .numberVal = 0});
    EXPECT_EQ(output.size(), 0);
    
    checkOperatorsAreCorrect(operators, {PLUS, MULTIPLY});
}

TEST(shuntingYardTests_followCountingRules, multiplyPlusCausesMultiplyToEnterOutput){
    vector<token> output = {};
    vector<token> operators = {};


    followCountingRules(output, operators, {.type = OPERATOR, .opType = MULTIPLY, .numberVal = 0});
    EXPECT_EQ(output.size(), 0);
    checkFirstTokenIsCorrectOperator(operators, MULTIPLY, 1);
    
    followCountingRules(output, operators, {.type = OPERATOR, .opType = PLUS, .numberVal = 0});
    checkOperatorsAreCorrect(output, {MULTIPLY});
    checkOperatorsAreCorrect(operators, {PLUS});
}