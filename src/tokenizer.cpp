#include "tokenizer.h"


pair <tokenType, string> verifyStringIsTokenType(
    const string input,
    int currentPosInString,
    const tokenType expectedTokenType,
    const std::map<const tokenType, vector<string>>& tokenToInputString
){
    for (const string& operatorStringToMatch : tokenToInputString.at(expectedTokenType)) {
        string substringFromPosition = input.substr(currentPosInString, operatorStringToMatch.size());
        //if strings are equal .compare returns 0, 
        if (substringFromPosition.compare(operatorStringToMatch) == 0) {
            return { expectedTokenType,  substringFromPosition };
        }
    }

    return { NONE, ""};
}


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

    int startOfToken = currentPosInString;
    pair<tokenType, string> result = verifyStringIsTokenType(input, currentPosInString, expectedTokenType, tokenToInputString);
    if (result.first != NONE) {
        currentPosInString += result.second.size();
        return { .type = result.first, .originalPosition = startOfToken};
    }

    return { .type = NONE };
}



tokenType findTokenType(
    const string input,
    int currentPosInString,
    const map<const tokenType, vector<string>>& tokenToInputString){

    for (auto it = tokenToInputString.begin(); it != tokenToInputString.end(); ++it) {
        tokenType expectedTokenType = it->first;
        tokenType type = verifyStringIsTokenType(input, currentPosInString, expectedTokenType, tokenToInputString).first;
        if (type != NONE) {
            return type;
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
    int startOfNumberToken = currentPosInString;

    if (numberString.size() > 0)
    {
        currentPosInString += numberString.size();
        token numberToken = {
                   .type = NUMBER,
                   .value = stoi(numberString),
                   .originalPosition = startOfNumberToken
        };
        return numberToken;
    }
    else {
        return { .type = NONE };
    }
};




token extractCustomDeclarationToken(
    const string input, 
    int& currentPosInString, 
    const map<const tokenType, vector<string>>& tokenToInputString,
    const map<string, int>& stringToID,
    tokenType customTokenType
) {
    int startOfCustomDeclarationToken = currentPosInString;
    for (const string& operatorStringToMatch : tokenToInputString.at(customTokenType)) {
        string substringFromPosition = input.substr(currentPosInString, operatorStringToMatch.size());
        //if strings are equal .compare returns 0, 
        if (substringFromPosition.compare(operatorStringToMatch) == 0) {
            currentPosInString += operatorStringToMatch.size();

            //we have found the string matching the custom token so lets get its id and return
            int tokenID = stringToID.at(substringFromPosition);
            return { .type = customTokenType, .value = tokenID, .originalPosition = startOfCustomDeclarationToken};
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
        return extractCustomDeclarationToken(
                input,
                currentPosInString,
                data.tokenToInputString,
                data.variableStringToID,
                VARIABLE);
    }
    else if (expectedTokenType == CUSTOM_FUNCTION) {
        return extractCustomDeclarationToken(
                input, 
                currentPosInString, 
                data.tokenToInputString, 
                data.functionStringToID, 
                CUSTOM_FUNCTION);
    }
    else{
        return extractNonNumberToken(input, currentPosInString, expectedTokenType, data.tokenToInputString);
    }

    return {};
};

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

string extractTokenDefinitionString(int& currentPosInString, const string input) {
    string variableString = "";

  
    for (int i = currentPosInString; i < input.size(); i++) {
        if (input[i] == ',') {
            currentPosInString = i;
            break;
        }

        variableString.push_back(input[i]);
       
    };
    return variableString;
}

token declareCustomToken(
    map<const tokenType, vector<string>> &tokenToInputString, 
    map<string, int> &stringToID, 
    map<int, vector<token>> &IDToExpression, 
    const string tokenString,
    tokenType customTokenType,
    vector<token> customDeclaration
    ) {
    token newCustomToken = {};
    if (stringToID.find(tokenString) != stringToID.end()) {
        //custom token exists so return a id assigned to the token
        int tokenID = stringToID.at(tokenString);
        newCustomToken = { .type = customTokenType, .value = tokenID };
    }
    else {
        //finally modify tokenData so that the program can use it in the future
        int tokenID = tokenToInputString[customTokenType].size() + 1;
        tokenToInputString[customTokenType].push_back(tokenString);
        stringToID.insert({ tokenString, tokenID });
        IDToExpression.insert({ tokenID, customDeclaration });
        newCustomToken = { .type = customTokenType, .value = tokenID };
    }

    return newCustomToken;
}


vector<token> extractNewVariableTokens(tokenData& data, int &currentPosInString, const string input) {
    //extract tokens from input so that we are at the symbols which define the string of the variable
    token createVariableFuncToken = extractToken(input, currentPosInString, FUNC_SET_VARIABLE, data);
    token leftParenthesis = extractToken(input, currentPosInString, PARENTHESE_LEFT, data);
    
    //extract the chars that define the variable
    string variableString = extractTokenDefinitionString(currentPosInString, input);

    token variableToken = {};
    variableToken = declareCustomToken( data.tokenToInputString,
                                                data.variableStringToID, 
                                                data.variableExpressions, 
                                                variableString, 
                                                VARIABLE, {{.type = NUMBER, .value=0}});
    //returns the tokens that were extracted
    return { createVariableFuncToken, leftParenthesis, variableToken };
}

vector<token> extractNewFunctionTokens(tokenData& data, int& currentPosInString, const string input) {
    //extract tokens from input so that we are at the symbols which define the string of the function
    token createFunctionToken = extractToken(input, currentPosInString, FUNC_SET_CUSTOM_FUNCTION, data);
    token leftParenthesis = extractToken(input, currentPosInString, PARENTHESE_LEFT, data);
   
    //extract the chars that define the function
    string functionString = extractTokenDefinitionString(currentPosInString, input);

    token functionToken = {};
    functionToken = declareCustomToken(data.tokenToInputString,
                                                data.functionStringToID,
                                                data.functionExpressions,
                                                functionString, 
                                                CUSTOM_FUNCTION, {});
   
    //createFunction should have a reference to what function token it is declaring
    createFunctionToken.value = functionToken.value;


    //returns the tokens that were extracted
    return { createFunctionToken, leftParenthesis, functionToken };
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
        expectedTokenType = findTokenType(input, currentPosInString, data.tokenToInputString);
        
        //if we have a token of SET_VARIABLE then we want to start keeping track of that variable for the future
        if (expectedTokenType == FUNC_SET_VARIABLE) {
            vector<token> tokensFromSetVariable = extractNewVariableTokens(data, currentPosInString, input);
            moveTokens(tokens, tokensFromSetVariable);
        }
        else if (expectedTokenType == FUNC_SET_CUSTOM_FUNCTION) {
            vector<token> tokensFromSetFunction = extractNewFunctionTokens(data, currentPosInString, input);
            moveTokens(tokens, tokensFromSetFunction);
        }
        //extract a token normally
        else {
            token nextToken = extractToken(input, currentPosInString, expectedTokenType, data);
            
            if (nextToken.type == NONE) {
                cout << "INCORRECT INPUT!\n";
                return {};
            }

            tokens.push_back(nextToken);

            //validation needs a rework disabled for the time being...
            /*
            if (!validTokensSoFar(tokens)){
                cout << "error found when tokenizing character at: " << currentPosInString << "\n";
                return {};
            }
            */
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
