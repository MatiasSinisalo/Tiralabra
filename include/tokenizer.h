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
    FUNC_SET_VARIABLE,
    FUNC_SET_CUSTOM_FUNCTION,

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
    FUNCTIONS, //SET_VARIABLE
    FUNCTIONS, //SET_CUSTOM_FUNCTION

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
    "FUNC_SET_VARIABLE",
    "FUNC_SET_CUSTOM_FUNCTION"

    "COMMA"
};



class token {
public:
    tokenType type;
    int value;
};


class tokenData {
public:
    //Currently all inputStrings must start with a unique character
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
        {FUNC_SET_VARIABLE, {"VARIABLE"}},
        {FUNC_SET_CUSTOM_FUNCTION, {"FUNCTION"}},

        {COMMA, {","}}
    };


    //once variable is defined the tokens defining the variable are stored here
    map<string, int> variableStringToID;
    map<int, vector<token>> variableExpressions; //this map probably does not need a vector of tokens since it only stores 1 token currently...

    //once function is definet the tokens of the function are stored here.
    map<string, int> functionStringToID;
    map<int, vector<token>> functionExpressions;

};

vector<token> getTokensFromInputString(const string input, tokenData &data);
token extractNonNumberToken(
        const string input,
        int& currentPosInString,
        const tokenType expectedTokenType,
        const std::map<const tokenType, vector<string>>& tokenToInputString);
tokenType findExpectedTokenType(
    const char c,
    const map<const tokenType, vector<string>>& tokenToInputString);
token extractNumberToken(const string input, int& currentPosInString);
//define DEBUG_PRINTS if debug output is needed from debug_printTokens function
//#define DEBUG_PRINTS
void debug_printTokens(const string extraMsg, const vector<token> tokens);
