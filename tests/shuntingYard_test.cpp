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


