#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForMultiplyPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
        .type = OP_PLUS
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForDividePlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};
    token newToken = {
        .type = OP_PLUS
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsTrueForDivideMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};
    token newToken = {
       .type = OP_MINUS
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, true);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForPlusDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_PLUS}};
    token newToken = {
            .type = OP_DIVIDE
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMinusDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MINUS}};
    token newToken = {
            .type = OP_DIVIDE
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};


TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForDivideMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};
    token newToken = {
            .type = OP_MULTIPLY
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMultiplyDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
           .type = OP_DIVIDE
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForPlusMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_PLUS}};
    token newToken = {
            .type = OP_MULTIPLY
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};

TEST(shuntingYardTests_isHigherPrecedence, returnsFalseForMinusMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MINUS}};
    token newToken = {
           .type = OP_MULTIPLY
    };
    bool isHigherPrecedence = beforeIsHigherPrecedence(output, operators, newToken);
    EXPECT_EQ(isHigherPrecedence, false);
};