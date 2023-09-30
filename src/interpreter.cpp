#include "interpreter.h"

token interpretFromRPN(const vector<token> tokensInRPN){
    vector<token> helperStack;
    //this loop does not go though the operators like they would be in a stack...
    //should go in reverse order of the vector.
    for(int i = 0; i< tokensInRPN.size(); i++){

        switch (tokensInRPN[i].type)
        {
        case NUMBER:
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

            evaluatedToken.numberVal = secondToken.numberVal + firstToken.numberVal;
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

            evaluatedToken.numberVal = secondToken.numberVal - firstToken.numberVal;
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

            evaluatedToken.numberVal = secondToken.numberVal * firstToken.numberVal;
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

            evaluatedToken.numberVal = secondToken.numberVal / firstToken.numberVal;
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

            evaluatedToken.numberVal = pow(secondToken.numberVal, firstToken.numberVal);
            helperStack.push_back(evaluatedToken);
            break;
        }
        case FUNC_SQRT:
        {
            token evaluatedToken;
            evaluatedToken.type = NUMBER;

            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();
            
            float firstTokenValueToFloat = float(firstToken.numberVal);
            float sqrtResult = sqrt(firstTokenValueToFloat);
            evaluatedToken.numberVal = sqrtResult;
            helperStack.push_back(evaluatedToken);
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