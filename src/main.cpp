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

void debug_printTokens(const string extraMsg, const vector<token> tokens){
    cout << extraMsg << "\n";
    cout << "[";
    for(const token &t : tokens){
        cout <<  tokenTypeToString[t.tokenType] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << ", ";
    }   
    cout << "]\n";
}

bool beforeIsLeftAssociative(vector<token> &output, vector<token> &operators){
    if(operators.size() > 0){
        token operatorBefore = operators.back();
        switch (operatorBefore.opType)
        {
            case MULTIPLY: // multiplty is left and right
            case MINUS: //minus is only left associative
            case PLUS: //plus is both left and right associative so it must also be handled
                return true;
                break;
            
            default:
                return false;
                break;
        }
    }
    return false;
}

bool beforeIsHigherPrecedence(vector<token> &output, vector<token> &operators){
    if(operators.size() > 0){
        token operatorBefore = operators.back();
        switch (operatorBefore.opType)
        {
            case MULTIPLY:
                return true;
                break;
            
            default:
                return false;
                break;
        }
    }
    return false;
}

//currently only supports + and -
//output should be Reverse Polish notation RPN
vector<token> shuntingYard(const vector<token> tokens){
    vector<token> output;
    vector<token> operators;
    for(const token &t : tokens){
        switch (t.tokenType)
        {
        case NUMBER:
            output.push_back(t);
            break;
        case OPERATOR:
            switch (t.opType)
            {
            case PLUS:
                if(beforeIsHigherPrecedence(output, operators) || beforeIsLeftAssociative(output, operators))
                {
                    token operatorBefore = operators.back();
                    output.push_back(operatorBefore);
                    operators.pop_back();
                }
                
                operators.push_back(t);
                break;
            case MINUS:
                if(beforeIsHigherPrecedence(output, operators) || beforeIsLeftAssociative(output, operators))
                {
                    token operatorBefore = operators.back();
                    output.push_back(operatorBefore);
                    operators.pop_back();
                }
                operators.push_back(t);
                break;
            case MULTIPLY:
                operators.push_back(t);
            default:
                break;
            }
        default:
            break;
        }
        
        debug_printTokens("output stack now is: ", output);

        debug_printTokens("operator stack now is: ", operators);
    }

    //add the rest of operators to the output in reverse since the vector is supposed to be a stack.
    for(int i = operators.size() - 1; i >= 0; i--){
        output.push_back(operators[i]);
    }
    operators.clear();

    return output;
}

int main(){
    string input = "";
    getline(cin, input);
    
    vector<token> tokens = getTokensFromInputString(input);

    for(token &t : tokens){
        cout << tokenTypeToString[t.tokenType] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << "\n";
    }

    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    return 0;
}