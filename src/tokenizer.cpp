#include "tokenizer.h"

bool nextIsTokenString(const string input, const int position, const string operatorStringToMatch){
    string substringFromPosition = input.substr(position, operatorStringToMatch.size());
    //if strings are equal .compare returns 0, 
    return substringFromPosition.compare(operatorStringToMatch) == 0;
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
//TODO: findExpectedOpType and  findExpectedFuncType look like they can be collapsed to a single function
operatorType findExpectedOpType(const char c){
    for(std::map<const operatorType, const std::string>::const_iterator it = operatorToInputString.begin(); it != operatorToInputString.end(); ++it){
        if(it->first != NONE && c == it->second.at(0)){
            return it->first; 
        }
    }
}

functionType findExpectedFuncType(const char c) {
    for (std::map<const functionType, const std::string>::const_iterator it = functionToInputString.begin(); it != functionToInputString.end(); ++it) {
        if (it->first != NONE && c == it->second.at(0)) {
            return it->first;
        }
    }
}

string extractNumberString(const string input, const int startIndex) {
    string numberString = "";
    for (int i = startIndex; i < input.size(); i++) {
        const char c = input.at(i);
        if (c == '0' ||
             c == '1' ||
             c == '2' ||
             c == '3' ||
             c == '4' ||
             c == '5' ||
             c == '6' ||
             c == '7' ||
             c == '8' ||
             c == '9'
            ) {
            numberString.push_back(c);
        }
        else {
            //this is the end of a number so break;
            break;
        }
    }
    return numberString;
}

//returns an token containing an operator
//currentPosInString will be incremented by lenght of the found token. 
//      currentPosInString += tokenString.size()
operatorType extractOperatorToken(const string input, int &currentPosInString){
    operatorType expectedOpType = NONE;
    const char c = input.at(currentPosInString);
    expectedOpType = findExpectedOpType(c);
    
    string expectedFollowingOperatorString = operatorToInputString.at(expectedOpType);
    if (nextIsTokenString(input, currentPosInString, expectedFollowingOperatorString)) {
        currentPosInString += expectedFollowingOperatorString.size();
        return expectedOpType;
    }

    return expectedOpType;
};

//returns an token containing an function
//currentPosInString will be incremented by lenght of the found token. 
//      currentPosInString += tokenString.size()
functionType extractFunctionToken(const string input, int& currentPosInString) {
    functionType expectedOpType = NONE_FUNCTION;
    const char c = input.at(currentPosInString);
    expectedOpType = findExpectedFuncType(c);

    string expectedFollowingOperatorString = functionToInputString.at(expectedOpType);
    if (nextIsTokenString(input, currentPosInString, expectedFollowingOperatorString)) {
        currentPosInString += expectedFollowingOperatorString.size();
        return expectedOpType;
    }

    return expectedOpType;
};

//returns an token containing a number value
//currentPosInString will be incremented by lenght of the found number. 
//      currentPosInString += number.size()
token extractNumberToken(const string input, int &currentPosInString){

    string numberString = extractNumberString(input, currentPosInString);

    currentPosInString += numberString.size();

    token numberToken = {
               .type = NUMBER,
               .opType = NONE,
               .numberVal = stoi(numberString)
    };

    return numberToken;
};

//TODO: Control flow of this function is quite tricky, it should be refactored to be more straight forward
vector<token> getTokensFromInputString(const string input){
    vector<token> tokens;
    const string powerOperator = "POWER";

    token nextToken = {};
    int currentPosInString = 0; 
    while (currentPosInString < input.size()){
        if (nextToken.type == NONE_TOKEN)
        {
            nextToken.type = extractExpectedTokenType(input, currentPosInString);
        }

        switch (nextToken.type)
        {
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
