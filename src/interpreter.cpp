#include "interpreter.h"


token getVariableValue(const token variableToken, const tokenData& data) {
    token variableValue = data.variableExpressions.at(variableToken.value)[0];
    return variableValue;
}

token getFunctionValue(const token functionToken, tokenData& data) {
    token result = interpretFromRPN(data.functionExpressions.at(functionToken.value), data);
    return result;
}

token popToken(vector<token>& src, tokenData& data) {
    if (src.size() == 0) {
        return {};
    }

    token token = src[src.size() - 1];
    src.pop_back();

    return token;
}


token popTokenAsValue(vector<token> &src, tokenData &data) {
    token token = popToken(src, data);
    

    switch (token.type)
    {
    case NUMBER:
        return token;
        break;
    case VARIABLE:
        return getVariableValue(token, data);
    case CUSTOM_FUNCTION:
        return getFunctionValue(token, data);
    default:
        //unsupported case, return NONE token
        return {};
        break;
    }
}

vector<token>  findCustomFunctionDeclaration(token functionToken, const tokenData &data) {
    if (data.functionExpressions.find(functionToken.value) != data.functionExpressions.end()) {
        vector<token> functionTokens = data.functionExpressions.at(functionToken.value);
        if (functionTokens.size() > 0) {
            return functionTokens;
        }
    }
    return {};
}


token interpretFromRPN(const vector<token> tokensInRPN, tokenData &data){
    vector<token> helperStack;
    for(int i = 0; i< tokensInRPN.size(); i++){

        switch (tokensInRPN[i].type)
        {

        case NUMBER:
        case VARIABLE:
            helperStack.push_back(tokensInRPN[i]);
            break;
        case CUSTOM_FUNCTION:
        {
            //interpret the function if there is a expression for it
            vector<token> functionTokens = findCustomFunctionDeclaration(tokensInRPN[i], data);
            if (functionTokens.size() > 0) {
                token result = interpretFromRPN(functionTokens, data);
                helperStack.push_back(result);
                break;
            }

            //pop tokens to helper stack until correct SET_CUSTOM_FUNCTION found
            int stopPoint = -1;
            for (int j = i + 1; j < tokensInRPN.size(); j++) {
                if (tokensInRPN[j].type == FUNC_SET_CUSTOM_FUNCTION && tokensInRPN[j].value == tokensInRPN[i].value) {
                    stopPoint = j;
                    break;
                }
                helperStack.push_back(tokensInRPN[j]);
            }
            if(stopPoint < 0){
                cout << "Expected a function declaration!\n";
                helperStack.push_back({});
                break;
            };
            //leave the main loop to point at the SET_CUSTOM_FUNCTION
            //take into acoount the i++ at the start of the main for loop
            i = stopPoint - 1;

            break;
        }
        case OP_PLUS:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);
            
            if (firstToken.type == NONE || secondToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }


            evaluatedToken.value = secondToken.value + firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_MINUS:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);

            if (firstToken.type == NONE || secondToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }

            evaluatedToken.value = secondToken.value - firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_MULTIPLY:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);

            if (firstToken.type == NONE || secondToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }


            evaluatedToken.value = secondToken.value * firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_DIVIDE:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);

            if (firstToken.type == NONE || secondToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }

            evaluatedToken.value = secondToken.value / firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_POWER:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);

            if (firstToken.type == NONE || secondToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }

            evaluatedToken.value = pow(secondToken.value, firstToken.value);
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SQRT:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            
            if (firstToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }

            float firstTokenValueToFloat = float(firstToken.value);
            float sqrtResult = sqrt(firstTokenValueToFloat);
            evaluatedToken.value = sqrtResult;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SET_VARIABLE:
        {
            token startingValueToken = popTokenAsValue(helperStack, data);
            if (startingValueToken.type == NONE) {
                cout << "Expected a value!\n";
                helperStack.push_back({});
                break;
            }

            token variableToken = popToken(helperStack, data);
            if (variableToken.type != VARIABLE) {
                cout << "Expected a variable!\n";
                helperStack.push_back({});
                break;
            }
            //assign the variable value to be firstToken
            data.variableExpressions.at(variableToken.value)[0] = startingValueToken;

            helperStack.push_back(startingValueToken);
            break;
        }
      
        case FUNC_SET_CUSTOM_FUNCTION:
        {

            if (findCustomFunctionDeclaration(tokensInRPN[i], data).size() > 0){
                cout << "Function already declared!\n";
                helperStack.push_back({});
                break;
            }


            //because of how CUSTOM_FUNCTION is treated when it is not declared the helperstack should now contain 
            //the expression for the function
            //copy the helper stack to the function expression
            data.functionExpressions.at(tokensInRPN[i].value) = helperStack;
            helperStack.clear();

            //return the evaluated expression

            helperStack.push_back({ .type = CUSTOM_FUNCTION, .value = tokensInRPN[i].value });
            break;
        }
        default:
            break;
        }
        
      
    }

    if(helperStack.size() > 1 || helperStack.size() == 0){
        cout << "interpreter encountered an error\n";
        debug_printTokens("token stack should be size 1 but it is: ", helperStack);
        return {};
    }

    token finalResult = popTokenAsValue(helperStack, data);
    return finalResult;
}