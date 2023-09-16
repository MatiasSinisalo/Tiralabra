#pragma once
#include "tokenizer.h"

void followCountingRules(vector<token>& output, vector<token>& operators, const token newToken);

bool beforeIsLeftAssociative(vector<token>& output, vector<token>& operators);

bool beforeIsHigherPrecedence(vector<token>& output, vector<token>& operators);

vector<token> shuntingYard(const vector<token> tokens);

