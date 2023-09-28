#include "interpreter.h"

token interpretFromRPN(const vector<token> tokensInRPN){
    token nextOperation = {.opType = NONE};
    vector<token> helperStack;
    //this loop does not go though the operators like they would be in a stack...
    //should go in reverse order of the vector.
    for(int i = 0; i< tokensInRPN.size(); i++){
        if(tokensInRPN[i].type == NUMBER){
            helperStack.push_back(tokensInRPN[i]);
        }
        else if(tokensInRPN[i].type == OPERATOR){
            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            
            token evaluatedToken;
            evaluatedToken.type = NUMBER;
            evaluatedToken.opType = NONE;
            switch (tokensInRPN[i].opType)
            {
            case PLUS:
                evaluatedToken.numberVal = secondToken.numberVal + firstToken.numberVal;
                helperStack.push_back(evaluatedToken);
                break;
            case MINUS:
                evaluatedToken.numberVal = secondToken.numberVal - firstToken.numberVal;
                helperStack.push_back(evaluatedToken);
                break;
            case MULTIPLY:
                evaluatedToken.numberVal = secondToken.numberVal * firstToken.numberVal;
                helperStack.push_back(evaluatedToken);
                break;
            case DIVIDE:
                evaluatedToken.numberVal = secondToken.numberVal / firstToken.numberVal;
                helperStack.push_back(evaluatedToken);
                break;
            default:
                break;
            }
        }
        else if (tokensInRPN[i].functionType == FUNCTION) {
            token firstToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();

            token secondToken = helperStack[helperStack.size() - 1];
            helperStack.pop_back();


            token evaluatedToken;
            evaluatedToken.type = NUMBER;
            evaluatedToken.opType = NONE;
            switch (tokensInRPN[i].opType == TO_POWER_OF)
            {
            case TO_POWER_OF:
                evaluatedToken.numberVal = pow(secondToken.numberVal, firstToken.numberVal);
                helperStack.push_back(evaluatedToken);
                break;
            default:
                break;
            }
        }
    }

    if(helperStack.size() > 1){
        cout << "SOMETHING WAS INCORRECT??\n";
        debug_printTokens("token stack should be size 1 but it is: ", helperStack);
    }

    return helperStack[0];
}