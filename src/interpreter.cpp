#include "interpreter.h"


token getVariableValue(const token variableToken, const tokenData& data) {
    token variableValue = data.variableExpressions.at(variableToken.value)[0];
    return variableValue;
}


token popTokenAsValue(vector<token> &src, const tokenData &data) {
    token token = src[src.size() - 1];
    src.pop_back();

    switch (token.type)
    {
    case NUMBER:
        return token;
        break;
    case VARIABLE:
        return getVariableValue(token, data);
    default:
        break;
    }
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
        case OP_PLUS:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            token secondToken = popTokenAsValue(helperStack, data);

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

            evaluatedToken.value = pow(secondToken.value, firstToken.value);
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SQRT:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = popTokenAsValue(helperStack, data);
            
            float firstTokenValueToFloat = float(firstToken.value);
            float sqrtResult = sqrt(firstTokenValueToFloat);
            evaluatedToken.value = sqrtResult;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SET_VARIABLE:
        {
            token startingValueToken = popTokenAsValue(helperStack, data);
    
            token variableToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            //assign the variable value to be firstToken
            data.variableExpressions.at(variableToken.value)[0] = startingValueToken;

            helperStack.push_back(startingValueToken);
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