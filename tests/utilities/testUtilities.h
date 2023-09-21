#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "tokenizer.h"
#include "shuntingYard.h"


void checkFirstTokenIsCorrectOperator(vector<token> tokens, operatorType expectedOperatorType, int expectedSize);
void checkOperatorsAreCorrect(vector<token> tokens, vector<operatorType> expectedOperators);

void checkTokensMatch(vector<token> tokensA, vector<token> tokensB);