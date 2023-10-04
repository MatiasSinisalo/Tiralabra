#include "interpreter.h"

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

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            evaluatedToken.value = secondToken.value + firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_MINUS:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            evaluatedToken.value = secondToken.value - firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_MULTIPLY:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            evaluatedToken.value = secondToken.value * firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case OP_DIVIDE:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            evaluatedToken.value = secondToken.value / firstToken.value;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_POWER:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            evaluatedToken.value = pow(secondToken.value, firstToken.value);
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SQRT:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            
            float firstTokenValueToFloat = float(firstToken.value);
            float sqrtResult = sqrt(firstTokenValueToFloat);
            evaluatedToken.value = sqrtResult;
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SET_VARIABLE:
        {
           

            //this should be a number by the time we execute SET_VARIABLE
            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            //this is the token for the variable
            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            //assign the variable value to be firstToken
            data.variableExpressions.at(secondToken.value) = { firstToken };

            token variableValue = data.variableExpressions.at(secondToken.value)[0];
            helperStack.push_back(variableValue);
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

    return helperStack[0];
}