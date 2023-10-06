#include "tokenizer.h"


//returns a token that is not a number
//currentPosInString will be incremented by lenght of the found token. 
//      currentPosInString += tokenString.size()
//return token of tokenType::NONE if token is not found
token extractNonNumberToken(
        const string input, 
        int & currentPosInString, 
        const tokenType expectedTokenType, 
        const std::map<const tokenType, vector<string>> &tokenToInputString) {
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




tokenType findExpectedTokenType(
    const char c, 
    const map<const tokenType, vector<string>> &tokenToInputString){
    for(std::map<const tokenType, vector<string>>::const_iterator it = tokenToInputString.begin(); it != tokenToInputString.end(); ++it){
        for (const string& s : it->second) {
            if (c == s.at(0)) {
                return it->first;
            }
        }
    }
    return NONE;
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
                   .value = stoi(numberString)
        };
        return numberToken;
    }
    else {
        return { .type = NONE };
    }
};


token extractVariableToken(const string input, int &currentPosInString, const tokenData& data){

    
    for (const string& operatorStringToMatch : data.tokenToInputString.at(VARIABLE)) {
        string substringFromPosition = input.substr(currentPosInString, operatorStringToMatch.size());
        //if strings are equal .compare returns 0, 
        if (substringFromPosition.compare(operatorStringToMatch) == 0) {
            currentPosInString += operatorStringToMatch.size();
            
            //we have found the string matching the variable so lets get its id and return the variable token
            int variableID = data.variableStringToID.at(substringFromPosition);
            return { .type = VARIABLE, .value = variableID };
        }
    }

    return { .type = NONE };
}

//Returns token if the input string contains a string of expectedTokenType
//Modifies currentPosInString to the next char after the expectedToken if string of expectedTokenType is found successfully.
//If function fails it returns token of tokenType::NONE and does not modify currentPosInString 
token extractToken(
    const string input, 
    int &currentPosInString, 
    const tokenType expectedTokenType, 
    const tokenData &data){
    
   
    if(expectedTokenType == NUMBER){
        return extractNumberToken(input, currentPosInString);
    }
    else if (expectedTokenType == VARIABLE) {
        return extractVariableToken(input, currentPosInString, data);
    }
    else{
        return extractNonNumberToken(input, currentPosInString, expectedTokenType, data.tokenToInputString);
    }

    return {};
};




bool validTokensSoFar(const vector<token> tokens) {
    if (tokens.size() >= 2) {
        token topToken = tokens[tokens.size() - 1];
        token secondToken = tokens[tokens.size() - 2];
        //Number should be before an operator
        if (tokenTypeToTokenFamily[topToken.type] == OPERATORS) {
            if (tokenTypeToTokenFamily[secondToken.type] != NUMBERS && tokenTypeToTokenFamily[secondToken.type] != VARIABLES) {
                cout << "expected an operator after number!\n";
                return false;
            }
        }

        //Left parenthesis should always be after operator
        if (tokenTypeToTokenFamily[secondToken.type] == FUNCTIONS) {
            if (topToken.type != PARENTHESE_LEFT) {
                cout << "expected '(' after function!\n";
                return false;
            }
        }
    }
    return true;
}

bool validParenthesis(const vector<token> tokens) {
    vector<token> helper;

    for (token t : tokens) {
        if (t.type == PARENTHESE_LEFT || t.type == PARENTHESE_RIGHT) {
            helper.push_back(t);
        }

        if (helper.size() >= 2) {
            token topToken = helper[helper.size() - 1];
            token secondToken = helper[helper.size() - 2];

            if (secondToken.type == PARENTHESE_LEFT && topToken.type == PARENTHESE_RIGHT) {
                helper.pop_back();
                helper.pop_back();
            }
        }
    }

    if (helper.size() > 0) {
        cout << "parenthese did not close correctly. \n";
        return false;
    }

    return true;
}

string extractVariableString(int& currentPosInString, const string input) {
    string variableString = "";

    int i = currentPosInString - 1;
    for (i < input.size(); i++;) {
        if (input[i] == ',') {
            break;
        }

        variableString.push_back(input[i]);
       
    };
    currentPosInString = i;
    return variableString;
}

vector<token> extractNewVariableTokens(tokenData& data, int &currentPosInString, const string input) {
    //extract tokens from input so that we are at the symbols which define the string of the variable
    token createVariableFuncToken = extractToken(input, currentPosInString, FUNC_SET_VARIABLE, data);
    token leftParenthesis = extractToken(input, currentPosInString, PARENTHESE_LEFT, data);
    
    //extract the chars that define the variable
    string variableString = extractVariableString(currentPosInString, input);

    token variableToken = {};
    if(data.variableStringToID.find(variableString) != data.variableStringToID.end()){
        //variable exists so return a id assigned to the variable
        int tokenID  = data.variableStringToID.at(variableString);
        variableToken = { .type = VARIABLE, .value = tokenID };
    }
    else{
        //finally modify tokenData so that the program can use it in the future
        int tokenID = data.tokenToInputString[VARIABLE].size() + 1;
        data.tokenToInputString[VARIABLE].push_back(variableString);
        data.variableStringToID.insert({ variableString, tokenID });
        data.variableExpressions.insert({ tokenID, {{.type = NUMBER, .value = 0}} });
        variableToken = { .type = VARIABLE, .value = tokenID };
    }
    //returns the tokens that were extracted
    return { createVariableFuncToken, leftParenthesis, variableToken };
}

void moveTokens(vector<token> &target, const vector<token> &src) {
    for (token t : src) {
        target.push_back(t);
    }
}

//TODO: Control flow of this function is quite tricky, it should be refactored to be more straight forward
vector<token> getTokensFromInputString(const string input, tokenData &data){
    vector<token> tokens;
   

   
    int currentPosInString = 0; 
    while (currentPosInString < input.size()){
        tokenType expectedTokenType = NONE;
        expectedTokenType = findExpectedTokenType(input.at(currentPosInString), data.tokenToInputString);
        
        //if we have a token of SET_VARIABLE then we want to start keeping track of that variable for the future
        if (expectedTokenType == FUNC_SET_VARIABLE) {
            vector<token> tokensFromSetVariable = extractNewVariableTokens(data, currentPosInString, input);
            moveTokens(tokens, tokensFromSetVariable);
        }
        //extract a token normally
        else {
            token nextToken = extractToken(input, currentPosInString, expectedTokenType, data);
            
            if (nextToken.type == NONE) {
                cout << "INCORRECT INPUT!\n";
                return {};
            }

            tokens.push_back(nextToken);

            if (!validTokensSoFar(tokens)){
                cout << "error found when tokenizing character at: " << currentPosInString << "\n";
                return {};
            }
        }
    }

    if (!validParenthesis(tokens)) {
        return {};
    }

    return tokens;
}




void debug_printTokens(const string extraMsg, const vector<token> tokens) {
    #ifdef DEBUG_PRINTS
        cout << extraMsg << "\n";
        cout << "[";
        for (const token& t : tokens) {
            cout << tokenTypeToString[t.type] << " ";
        }
        cout << "]\n";
    #endif
}
