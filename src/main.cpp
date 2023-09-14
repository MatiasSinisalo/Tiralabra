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

//currently only supports + and -
//output should be Reverse Polish notation RPN
vector<token> shuntingYard(const vector<token> tokens){
    int numbersBeforeOperator = 0;
    vector<token> output;
    vector<token> operators;
    for(const token &t : tokens){
        switch (t.tokenType)
        {
        case NUMBER:
            output.push_back(t);
            numbersBeforeOperator++;
            break;
        case OPERATOR:
            switch (t.opType)
            {
            case PLUS:
                operators.push_back(t);
                break;
            case MINUS:
                operators.push_back(t);
                break;
            default:
                break;
            }
        default:
            break;
        }
        //check if there are two numbers in the output if there is, join the operators to the end of output
        if(numbersBeforeOperator == 2){
            output.insert(output.end(), operators.begin(), operators.end());
            operators.clear();
            numbersBeforeOperator = 1; // the result of A B (OPERATOR) => C so numbersBefore = 1 
        }
        debug_printTokens("output stack now is: ", output);

        debug_printTokens("operator stack now is: ", operators);
    }
    
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



