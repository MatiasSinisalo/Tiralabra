#pragma once
#include <iostream>
#include <vector>
#include <regex>
using namespace std;


enum tokenType {
    NUMBER,
    OPERATOR
};

const vector<string> tokenTypeToString = {
    "NUMBER",
    "OPERATOR",
};

enum operatorType {
    NONE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

const vector<string> operatorTypeToString = {
    "NONE",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE"
};

class token {
public:
    tokenType tokenType;

    operatorType opType;
    int numberVal;
};

vector<token> getTokensFromInputString(const string input);
void debug_printTokens(const string extraMsg, const vector<token> tokens);