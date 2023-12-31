#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "tokenizer.h"
#include "shuntingYard.h"

using namespace std;


TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatPlusIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_PLUS}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatMinusIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MINUS}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatMultiplyIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_MULTIPLY}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};

TEST(shuntingYardTests_beforeIsLeftAssociative, detectsThatDivideIsLeftAsscociative){
    vector<token> output = {};
    vector<token> operators = {{.type = OP_DIVIDE}};

    bool isLeftAssociative = beforeIsLeftAssociative(output, operators);
    EXPECT_EQ(isLeftAssociative, true);
};