#include "main.h"


enum tokenType{
    NUMBER,
    OPERATOR
};

const vector<string> tokenTypeToString = {
    "NUMBER",
    "OPERATOR",
};

enum operatorType{
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

class token{
public:
    tokenType tokenType;

    operatorType opType;
    int numberVal;
};


vector<token> getTokensFromInputString(const string input){
    vector<token> tokens;
    const regex numberRegex("[0-9]");
    const regex operatorRegex("[\\+|\\-|\\*|\\/]");
    smatch matchNumber;
    smatch matchOperator;
    for(int i = 0; i < input.size(); i++){
        string string_char = input.substr(i, 1);
        cout << string_char << "\n";
        bool confirmedNumber = regex_match(string_char, matchNumber, numberRegex);
        bool confirmedOperator = regex_match(string_char, matchOperator, operatorRegex);
        
        if(confirmedNumber){
            cout << "is number!\n";
            tokens.push_back({
                .tokenType = NUMBER, 
                .opType = NONE, 
                .numberVal= stoi(string_char)
            });
        }
        else if(confirmedOperator){
            cout << "is operator!\n";
            token newToken{
                .tokenType = OPERATOR,
            };
            if(string_char == "+")
            {
                newToken.opType = PLUS;
            }
            else if(string_char == "-")
            {
                newToken.opType = MINUS;
            }
            else if(string_char == "/")
            {
                newToken.opType = DIVIDE;
            }
             else if(string_char == "*")
            {
                newToken.opType = MULTIPLY;
            }
            tokens.push_back(newToken);
        }
    }

    return tokens;
}

int main(){
    

    string input = "";
    getline(cin, input);
    
    vector<token> tokens = getTokensFromInputString(input);

    for(token &t : tokens){
        cout << tokenTypeToString[t.tokenType] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << "\n";
    }
    
    return 0;
}

