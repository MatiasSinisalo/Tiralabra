#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;
TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatPlusIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatMinusIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MINUS}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatMultiplyIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatDivideIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = DIVIDE}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForMultiplyPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};
    token newToken = {
        .type = OPERATOR,
        .opType = PLUS,
        .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForDividePlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = DIVIDE}};
    token newToken = {
        .type = OPERATOR,
        .opType = PLUS,
        .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForDivideMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = DIVIDE}};
    token newToken = {
        .type = OPERATOR,
        .opType = MINUS,
        .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForPlusDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMinusDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MINUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};



TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForPlusMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMinusMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MINUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForPlusPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMinusPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MINUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForPlusMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};
    token newToken = {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};


TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMultiplyMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};
    token newToken = {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMultiplyDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};
    token newToken = {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForDivideMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = DIVIDE}};
    token newToken = {
            .type = OPERATOR,
            .opType = MULTIPLY,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForDivideDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = DIVIDE}};
    token newToken = {
            .type = OPERATOR,
            .opType = DIVIDE,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsFalseForMultiplyPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};
    token newToken = {
            .type = OPERATOR,
            .opType = PLUS,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, false);
};

TEST(shuntingYardTests_isSamePrecedence, returnsFalseForMultiplyMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};
    token newToken = {
            .type = OPERATOR,
            .opType = MINUS,
            .numberVal = 0
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, false);
};

TEST(shuntingYardTests_isSamePrecedence, returnsFalseForEmptyInputs){
    vector<token> output = {};
    vector<token> operators = {};
    token newToken = {
            
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, false);
};

void checkFirstTokenIsCorrectOperator(vector<token> tokens, operatorType expectedOperatorType, int expectedSize){
    EXPECT_EQ(tokens.size(), expectedSize);
    EXPECT_EQ(tokens[tokens.size() - 1].type, OPERATOR);
    EXPECT_EQ(tokens[tokens.size() - 1].opType, expectedOperatorType);
}

void checkOperatorsAreCorrect(vector<token> tokens, vector<operatorType> expectedOperators){
    EXPECT_EQ(tokens.size(), expectedOperators.size());
    for(int i = 0; i < tokens.size(); i++){
        EXPECT_EQ(tokens[i].type, OPERATOR);
        EXPECT_EQ(tokens[i].opType, expectedOperators[i]);
    }
}

void checkTokensMatch(vector<token> tokensA, vector<token> tokensB){
    EXPECT_EQ(tokensA.size(), tokensB.size());
    for(int i = 0; i < tokensA.size(); i++){
        EXPECT_EQ(tokensA[i].type, tokensB[i].type);
        EXPECT_EQ(tokensA[i].opType, tokensB[i].opType);
        EXPECT_EQ(tokensA[i].numberVal, tokensB[i].numberVal);
    }
}

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