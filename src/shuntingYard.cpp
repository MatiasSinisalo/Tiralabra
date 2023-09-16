#include "shuntingYard.h"

bool beforeIsLeftAssociative(vector<token>& output, vector<token>& operators) {
    if (operators.size() > 0) {
        token operatorBefore = operators.back();
        switch (operatorBefore.opType)
        {
        case MULTIPLY: // multiplty is left and right
        case MINUS: //minus is only left associative
        case PLUS: //plus is both left and right associative so it must also be handled
            return true;
            break;

        default:
            return false;
            break;
        }
    }
    return false;
}

bool beforeIsHigherPrecedence(vector<token>& output, vector<token>& operators, const token compareTo) {
    if (operators.size() > 0) {
        token operatorBefore = operators.back();
        if(operatorBefore.opType == MULTIPLY || operatorBefore.opType == DIVIDE){
            if(compareTo.opType == MINUS || compareTo.opType == PLUS){
                return true;
            }
        }
        return false;
    }
    return false;
}

bool beforeIsSamePrecedence(const vector<token>& output, const vector<token>& operators, const token compareTo){
    if(operators.size() > 0){
        const token beforeToken = operators.back();
        if(beforeToken.opType == compareTo.opType){
            return true;
        }
        else if(beforeToken.opType == MINUS && compareTo.opType == PLUS){
            return true;
        }
        else if(beforeToken.opType == PLUS && compareTo.opType == MINUS){
            return true;
        }
        else if(beforeToken.opType == MULTIPLY && compareTo.opType == DIVIDE){
            return true;
        }
        else if(beforeToken.opType == DIVIDE && compareTo.opType == MULTIPLY){
            return true;
        }
        return false;
    }
   return false;
}

void followCountingRules(vector<token>& output, vector<token>& operators, const token newToken) {
    if (beforeIsHigherPrecedence(output, operators, newToken) || (beforeIsSamePrecedence(output, operators, newToken) && beforeIsLeftAssociative(output, operators)))
    {
        token operatorBefore = operators.back();
        output.push_back(operatorBefore);
        operators.pop_back();
    }
    operators.push_back(newToken);
}

//currently only supports +, - and *
//output should be Reverse Polish notation RPN
vector<token> shuntingYard(const vector<token> tokens) {
    vector<token> output;
    vector<token> operators;
    for (const token& t : tokens) {
        switch (t.type)
        {
        case NUMBER:
            output.push_back(t);
            break;
        case OPERATOR:
            followCountingRules(output, operators, t);
            break;
        default:
            break;
        }

        debug_printTokens("output stack now is: ", output);

        debug_printTokens("operator stack now is: ", operators);
    }

    //add the rest of operators to the output in reverse since the vector is supposed to be a stack.
    for (int i = operators.size() - 1; i >= 0; i--) {
        output.push_back(operators[i]);
    }
    operators.clear();

    return output;
}
