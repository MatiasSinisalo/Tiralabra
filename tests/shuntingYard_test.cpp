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

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MULTIPLY}};

    bool isLeftAssociative = beforeIsHigherPrecedence(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = PLUS}};

    bool isLeftAssociative = beforeIsHigherPrecedence(output, operators);
    EXPECT_EQ(isLeftAssociative, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OPERATOR, .opType = MINUS}};

    bool isLeftAssociative = beforeIsHigherPrecedence(output, operators);
    EXPECT_EQ(isLeftAssociative, false);
};
