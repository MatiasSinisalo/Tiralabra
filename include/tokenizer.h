#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <map>
using namespace std;


enum tokenType {
    NONE,
    
    NUMBER,
    
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,

    PARENTHESE_LEFT,
    PARENTHESE_RIGHT,
    
    FUNC_POWER,
};

const vector<string> tokenTypeToString = {
    "NONE_TOKEN",
    "NUMBER",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "PARENTHESE_LEFT",
    "PARENTHESE_RIGHT",
    "TO_POWER_OF"
};

const map<const tokenType, const string> tokenToInputString = {
    {NONE, ""},
    {NUMBER, ""},

    {OP_PLUS, "+"},
    {OP_MINUS, "-"},
    {OP_MULTIPLY, "*"},
    {OP_DIVIDE, "/"},
    
    {PARENTHESE_LEFT, "("},
    {PARENTHESE_RIGHT, ")"},
    
    {FUNC_POWER, "POWER"}
};

class token {
public:
    tokenType type;
    int numberVal;
};

vector<token> getTokensFromInputString(const string input);
//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
