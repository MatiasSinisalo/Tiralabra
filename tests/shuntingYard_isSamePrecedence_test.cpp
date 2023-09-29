#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;




TEST(shuntingYardTests_isSamePrecedence, returnsTrueForPlusPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_PLUS}};
    token newToken = {
            .type = OP_PLUS,
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMinusPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MINUS}};
    token newToken = {
           .type = OP_PLUS
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForPlusMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_PLUS}};
    token newToken = {
            .type = OP_MINUS
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};


TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMultiplyMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
            .type = OP_MULTIPLY
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForMultiplyDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
            .type = OP_DIVIDE
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForDivideMultiply){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};
    token newToken = {
           .type = OP_MULTIPLY
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsTrueForDivideDivide){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};
    token newToken = {
           .type = OP_DIVIDE
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, true);
};

TEST(shuntingYardTests_isSamePrecedence, returnsFalseForMultiplyPlus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
           .type = OP_PLUS
    };
    bool isSamePrecedence = beforeIsSamePrecedence(output, operators, newToken);
    EXPECT_EQ(isSamePrecedence, false);
};

TEST(shuntingYardTests_isSamePrecedence, returnsFalseForMultiplyMinus){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};
    token newToken = {
           .type = OP_MINUS
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
