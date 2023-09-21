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
    tokenType type;

    operatorType opType;
    int numberVal;
};

vector<token> getTokensFromInputString(const string input);

//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
//#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
