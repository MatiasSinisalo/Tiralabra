#include "tokenizer.h"

bool nextIsTokenString(const string input, const int position, const string operatorStringToMatch){
    string substringFromPosition = input.substr(position, operatorStringToMatch.size());
    //if strings are equal .compare returns 0, 
    return substringFromPosition.compare(operatorStringToMatch) == 0;
}



//TODO: findExpectedOpType and  findExpectedFuncType look like they can be collapsed to a single function
tokenType findExpectedTokenType(const char c){
    for(std::map<const tokenType, const std::string>::const_iterator it = tokenToInputString.begin(); it != tokenToInputString.end(); ++it){
        if(it->first != NONE && c == it->second.at(0)){
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



//Returns token if the input string contains a string of expectedTokenType
//Modifies currentPosInString to the next char after the expectedToken if string of expectedTokenType is found successfully.
//If function fails it returns token of tokenType::NONE and does not modify currentPosInString 
token extractToken(const string input, int &currentPosInString, const tokenType expectedTokenType){  
    string expectedFollowingOperatorString = tokenToInputString.at(expectedTokenType);
    
    if (expectedTokenType != NUMBER && nextIsTokenString(input, currentPosInString, expectedFollowingOperatorString)) {
        currentPosInString += expectedFollowingOperatorString.size();
        return { .type = expectedTokenType };
    }
    else if(expectedTokenType == NUMBER){
        return extractNumberToken(input, currentPosInString);
    }

    return {};
};


//returns an token containing a number value
//currentPosInString will be incremented by lenght of the found number. 
//      currentPosInString += number.size()
token extractNumberToken(const string input, int &currentPosInString){

    string numberString = extractNumberString(input, currentPosInString);

    
    currentPosInString += numberString.size();

    token numberToken = {
               .type = NUMBER,
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
        tokenType expectedTokenType = NONE;
        expectedTokenType = findExpectedTokenType(input.at(currentPosInString));
        

        nextToken = extractToken(input, currentPosInString, nextToken.type);

        if (nextToken.type == NONE) {
            cout << "INCORRECT INPUT!";
            return {};
        }
        
    }
    return tokens;
}




void debug_printTokens(const string extraMsg, const vector<token> tokens) {
    #ifdef DEBUG_PRINTS
        cout << extraMsg << "\n";
        cout << "[";
        for (const token& t : tokens) {
            cout << tokenTypeToString[t.type];
        }
        cout << "]\n";
    #endif
}
