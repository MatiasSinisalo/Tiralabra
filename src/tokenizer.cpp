#include "tokenizer.h"

bool nextIsOperator(const string input, const int position, const string operatorStringToMatch){
    string substringFromPosition = input.substr(position, operatorStringToMatch.size());
    //if strings are equal .compare returns 0, 
    return substringFromPosition.compare(operatorStringToMatch) == 0;
}



vector<token> getTokensFromInputString(const string input) {
    
    vector<token> tokens = getTokensFromInputString_v2(input);
    return tokens;

    /*
    const string powerOperator = "POWER";
    const regex numberRegex("[0-9]");
    const regex operatorRegex("[\\+|\\-|\\*|\\/|(|)|P|]");
    smatch matchNumber;
    smatch matchOperator;
    for (int i = 0; i < input.size(); i++) {
        string string_char = input.substr(i, 1);
        
        bool confirmedNumber = regex_match(string_char, matchNumber, numberRegex);
        bool confirmedOperator = regex_match(string_char, matchOperator, operatorRegex);

        if (confirmedNumber) {
            
            tokens.push_back({
                .type = NUMBER,
                .opType = NONE,
                .numberVal = stoi(string_char)
            });
        }
        else if (confirmedOperator) {
            
            token newToken{
                .type = OPERATOR,
            };
            if (string_char == "+")
            {
                newToken.opType = PLUS;
            }
            else if (string_char == "-")
            {
                newToken.opType = MINUS;
            }
            else if (string_char == "/")
            {
                newToken.opType = DIVIDE;
            }
            else if (string_char == "*")
            {
                newToken.opType = MULTIPLY;
            }
            else if (string_char == "(")
            {
                newToken.opType = PARENTHESE_LEFT;
            }
            else if (string_char == ")")
            {
                newToken.opType = PARENTHESE_RIGHT;
            }
            else if (string_char == "P")
            {
                if(nextIsOperator(input, i, powerOperator))
                {
                    newToken.opType = TO_POWER_OF;
                    i += powerOperator.size() - 1;
                }
            }
            tokens.push_back(newToken);
        }
    }

    return tokens;
    */
}

//returns expected tokenType for the char at the current location
tokenType extractExpectedTokenType(const string input, const int currentPosInString){
    
    const char c = input.at(currentPosInString);
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return tokenType::NUMBER;
        break;
    case 'P':
    case '+':
    case '-':
    case '/':
    case '*':
    case '(':
    case ')':
        return tokenType::OPERATOR;
        break;
    default:
        break;
    }
    
    return tokenType::NONE_TOKEN;
};

operatorType extractSingleCharTokens(){
    return {};
}

operatorType findExpectedOpType(const char c){
    for(std::map<const operatorType, const std::string>::const_iterator it = operatorToInputString.begin(); it != operatorToInputString.end(); ++it){
        if(it->first != NONE && c == it->second.at(0)){
            return it->first; 
        }
    }
}

//advances currentPosInString until an entire operatorToken is found and returns an token containing the operator
operatorType extractOperatorToken(const string input, int &currentPosInString){
    int sizeOfExpectedOperatorTokenString = 0;
    operatorType expectedOpType = NONE;
   
    while (currentPosInString < input.size()){
        

        const char c = input.at(currentPosInString);
        if(sizeOfExpectedOperatorTokenString == 0){
            expectedOpType = findExpectedOpType(c);
        }
        else{
            //check that current char matches the expected operator char
            const string comparisonString = operatorToInputString.find(expectedOpType)->second;
            if (sizeOfExpectedOperatorTokenString == comparisonString.size())
            {
                currentPosInString++;
                return expectedOpType;
            }
            else if (sizeOfExpectedOperatorTokenString > comparisonString.size()) {
                return operatorType::NONE;
            }
            if(c != comparisonString.at(sizeOfExpectedOperatorTokenString - 1))
            {
                return operatorType::NONE;
            }
           
            currentPosInString++;
        }
        sizeOfExpectedOperatorTokenString++;
       
    }
    return expectedOpType;
};

//advances currentPosInString until a number is found and returns and token containing the number
token extractNumberToken(const string input, int &currentPosInString){
    string numberString = "";
    while (currentPosInString < input.size()) {
        
        const char c = input.at(currentPosInString);
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            numberString.push_back(c);
            break;
        default:
            //we encountered something else than a number
            token numberToken = {
                .type = NUMBER,
                .opType = NONE,
                .numberVal = stoi(numberString)
            };
            return numberToken;
            break;
        }
        
        currentPosInString++;
        if (currentPosInString >= input.size())
        {
            token numberToken = {
                .type = NUMBER,
                .opType = NONE,
                .numberVal = stoi(numberString)
            };
            return numberToken;
        }

    }
  
    return {};
};

//TODO: Control flow of this function is quite tricky, it should be refactored to be more straight forward
vector<token> getTokensFromInputString_v2(const string input){
    vector<token> tokens;
    const string powerOperator = "POWER";

    token nextToken = {};
    int currentPosInString = 0; 
    while (currentPosInString < input.size()){
       
        switch (nextToken.type)
        {
        case NONE_TOKEN:
            nextToken.type = extractExpectedTokenType(input, currentPosInString);
            
            if(nextToken.type == tokenType::NONE_TOKEN){
                currentPosInString++;
                continue;
            }
            break;
        case OPERATOR:
            nextToken.opType = extractOperatorToken(input, currentPosInString);
            tokens.push_back(nextToken);
            nextToken = {};
            break;
        case NUMBER:
            nextToken = extractNumberToken(input, currentPosInString);
            tokens.push_back(nextToken);
            nextToken = {};
            break;
        default:
            currentPosInString++;
            break;
        }
        
    }
    return tokens;
}




void debug_printTokens(const string extraMsg, const vector<token> tokens) {
    #ifdef DEBUG_PRINTS
        cout << extraMsg << "\n";
        cout << "[";
        for (const token& t : tokens) {
            cout << tokenTypeToString[t.type] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << ", ";
        }
        cout << "]\n";
    #endif
}
