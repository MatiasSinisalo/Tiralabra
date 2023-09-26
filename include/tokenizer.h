#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <map>
using namespace std;


enum tokenType {
    NONE_TOKEN,
    NUMBER,
    OPERATOR,
};

const vector<string> tokenTypeToString = {
    "NONE_TOKEN",
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
    TO_POWER_OF,
};

const map<const operatorType, const string> operatorToInputString = {
    {NONE, ""},
    {PLUS, "+"},
    {MINUS, "-"},
    {MULTIPLY, "*"},
    {DIVIDE, "/"},
    {PARENTHESE_LEFT, "("},
    {PARENTHESE_RIGHT, ")"},
    {TO_POWER_OF, "POWER"}
};

const vector<string> operatorTypeToString = {
    "NONE",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "PARENTHESE_LEFT",
    "PARENTHESE_RIGHT",
    "TO_POWER_OF"
};

class token {
public:
    tokenType type;
    operatorType opType;
    int numberVal;
};

vector<token> getTokensFromInputString(const string input);
vector<token> getTokensFromInputString_v2(const string input);
//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
