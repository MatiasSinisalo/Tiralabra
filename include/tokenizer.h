#pragma once
#include <iostream>
#include <vector>
#include <regex>
using namespace std;


enum tokenType {
    NUMBER,
    OPERATOR,
    FUNCTION
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
    DIVIDE,
    PARENTHESE_LEFT, // => (
    PARENTHESE_RIGHT, // =>  )
};

const vector<string> operatorTypeToString = {
    "NONE",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "PARENTHESE_LEFT",
    "PARENTHESE_RIGHT"
};

class token {
public:
    tokenType type;
    operatorType opType;
    int numberVal;
    //an ID to look up the tokens function
    uint64_t functionID;
};

vector<token> getTokensFromInputString(const string input);

//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
//#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
