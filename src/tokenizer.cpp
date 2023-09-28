#include "tokenizer.h"


//returns a token that is not a number
//currentPosInString will be incremented by lenght of the found token. 
//      currentPosInString += tokenString.size()
//return token of tokenType::NONE if token is not found
token extractNonNumberToken(const string input, int & currentPosInString, const tokenType expectedTokenType) {
    if (expectedTokenType == NUMBER) {
        cout << "ERROR IN TOKEN PHASE \n";
        return { .type = NONE };
    }

    for (const string& operatorStringToMatch : tokenToInputString.at(expectedTokenType)){
        string substringFromPosition = input.substr(currentPosInString, operatorStringToMatch.size());
        //if strings are equal .compare returns 0, 
        if (substringFromPosition.compare(operatorStringToMatch) == 0) {
            currentPosInString += operatorStringToMatch.size();
                return { .type = expectedTokenType };
        }
    }

    return { .type = NONE };
}




tokenType findExpectedTokenType(const char c){
    for(std::map<const tokenType, const vector<string>>::const_iterator it = tokenToInputString.begin(); it != tokenToInputString.end(); ++it){
        for (const string& s : it->second) {
            if (c == s.at(0)) {
                return it->first;
            }
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

//returns an token containing a number value
//currentPosInString will be incremented by lenght of the found number. 
//      currentPosInString += number.size()
//return token of tokenType::NONE if number is not found
token extractNumberToken(const string input, int& currentPosInString) {

    string numberString = extractNumberString(input, currentPosInString);

    if (numberString.size() > 0)
    {
        currentPosInString += numberString.size();
        token numberToken = {
                   .type = NUMBER,
                   .numberVal = stoi(numberString)
        };
        return numberToken;
    }
    else {
        return { .type = NONE };
    }
};

//Returns token if the input string contains a string of expectedTokenType
//Modifies currentPosInString to the next char after the expectedToken if string of expectedTokenType is found successfully.
//If function fails it returns token of tokenType::NONE and does not modify currentPosInString 
token extractToken(const string input, int &currentPosInString, const tokenType expectedTokenType){  
    
    if (expectedTokenType != NUMBER){
        return extractNonNumberToken(input, currentPosInString, expectedTokenType);
    }
    else if(expectedTokenType == NUMBER){
        return extractNumberToken(input, currentPosInString);
    }

    return {};
};




//TODO: Control flow of this function is quite tricky, it should be refactored to be more straight forward
vector<token> getTokensFromInputString(const string input){
    vector<token> tokens;
    const string powerOperator = "POWER";

   
    int currentPosInString = 0; 
    while (currentPosInString < input.size()){
        tokenType expectedTokenType = NONE;
        expectedTokenType = findExpectedTokenType(input.at(currentPosInString));
        

        token nextToken = extractToken(input, currentPosInString, expectedTokenType);

        if (nextToken.type == NONE) {
            cout << "INCORRECT INPUT!";
            return {};
        }

        tokens.push_back(nextToken);
        
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
