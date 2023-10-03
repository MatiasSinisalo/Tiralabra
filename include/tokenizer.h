#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <map>
using namespace std;


enum tokenType {
    NONE,
    
    NUMBER,
    VARIABLE,

    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,

    PARENTHESE_LEFT,
    PARENTHESE_RIGHT,
    
    FUNC_POWER,
    FUNC_SQRT,

    COMMA,
};

enum tokenFamily {
    NONE_FAMILY,
    NUMBERS,
    VARIABLES,
    OPERATORS,
    FUNCTIONS,
    STRUCTURES,
};


const vector<tokenFamily> tokenTypeToTokenFamily = {
    NONE_FAMILY, //NONE
   
    NUMBERS, //Number
    VARIABLES, //VARIABLE

    OPERATORS, // +
    OPERATORS, // -
    OPERATORS, // *
    OPERATORS, // /

    STRUCTURES, // (
    STRUCTURES, // )

    FUNCTIONS, // POWER
    FUNCTIONS, // SQRT

    STRUCTURES // ,
};

const vector<string> tokenTypeToString = {
    "NONE",
    
    "NUMBER",
    "VARIABLE",

    "OP_PLUS",
    "OP_MINUS",
    "OP_MULTIPLY",
    "OP_DIVIDE",
    
    "PARENTHESE_LEFT",
    "PARENTHESE_RIGHT",
    
    "FUNC_POWER",
    "FUNC_SQRT",

    "COMMA"
};



class token {
public:
    tokenType type;
    int numberVal;
};


class tokenData {
public:
    map<const tokenType, vector<string>> tokenToInputString = {
        {NONE, {}},

        {NUMBER, {"0", "1", "2",  "3", "4", "5", "6", "7", "8", "9"}},
        {VARIABLE, {}}, // variable inputStrings are at the start empty, since there are no variables to start with

        {OP_PLUS, {"+"}},
        {OP_MINUS, {"-"}},
        {OP_MULTIPLY, {"*"}},
        {OP_DIVIDE, {"/"}},

        {PARENTHESE_LEFT, {"("}},
        {PARENTHESE_RIGHT, {")"}},

        {FUNC_POWER, {"POWER"}},
        {FUNC_SQRT, {"SQRT"}},

        {COMMA, {","}}
    };

    //once variable is defined the tokens defining the variable are stored here
    map<string, vector<token>> variableStringToExpression;
};

vector<token> getTokensFromInputString(const string input, tokenData &data);
token extractNonNumberToken(const string input, int & currentPosInString, const tokenType expectedTokenType);
tokenType findExpectedTokenType(const char c);
token extractNumberToken(const string input, int& currentPosInString);
//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
//#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
