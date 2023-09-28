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
    FUNCTION
};

const vector<string> tokenTypeToString = {
    "NONE_TOKEN",
    "NUMBER",
    "OPERATOR",
    "FUNCTION",
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

const map<const operatorType, const string> operatorToInputString = {
    {NONE, ""},
    {PLUS, "+"},
    {MINUS, "-"},
    {MULTIPLY, "*"},
    {DIVIDE, "/"},
    {PARENTHESE_LEFT, "("},
    {PARENTHESE_RIGHT, ")"},
};

const vector<string> operatorTypeToString = {
    "NONE",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "PARENTHESE_LEFT",
    "PARENTHESE_RIGHT",
};

enum functionType {
    NONE_FUNCTION,
    TO_POWER_OF,
};

const map<const functionType, const string> functionToInputString = {
    {NONE_FUNCTION, ""},
    {TO_POWER_OF, "POWER"}
};

const vector<string> functionTypeToString = {
    "NONE_FUNCTION",
    "POWER"
};

//TODO: this class is super easy to use incorrectly, refactor needed
class token {
public:
    tokenType type;
    operatorType opType;
    functionType functionType;
    int numberVal;
};

vector<token> getTokensFromInputString(const string input);
//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
