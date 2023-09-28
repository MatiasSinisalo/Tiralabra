#include "shuntingYard.h"

bool beforeIsLeftAssociative(vector<token>& output, vector<token>& operators) {
    if (operators.size() > 0) {
        token operatorBefore = operators.back();
        if (operatorBefore.functionType == TO_POWER_OF) {
            return true;
        }
        switch (operatorBefore.opType)
        {
        case MULTIPLY: // multiplty is left and right
        case MINUS: //minus is only left associative
        case PLUS: //plus is both left and right associative so it must also be handled
        case DIVIDE: //divide is left associative
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
        if(operatorBefore.opType == MULTIPLY || operatorBefore.opType == DIVIDE || operatorBefore.functionType == TO_POWER_OF){
            if(compareTo.opType == MINUS || compareTo.opType == PLUS){
                return true;
            }
        }

        //example:
        //in case of POWER(2,3)/2, the calculator should evaluate the POWER(2,3) before the /2,
        //since the value of POWER(2,3) would not be known
        //same for POWER(2,3)*2
        if (operatorBefore.functionType == TO_POWER_OF) {
            if (compareTo.opType == MULTIPLY || compareTo.opType == DIVIDE) {
                return true;
            }
        };
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
        else if (beforeToken.functionType == TO_POWER_OF && compareTo.functionType == TO_POWER_OF) {
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

void popTokensBeforeLeftParenthesis(vector<token> &target, vector<token> &source){
    int stoppingIndex = 0;
    for (int i = source.size() - 1; i >= 0; i--) {
        if(source[i].type == OPERATOR){
            if(source[i].opType == PARENTHESE_LEFT){
                stoppingIndex = i;
                break;
            }
        }
        target.push_back(source[i]);
    }
    source.erase(source.begin()+ stoppingIndex, source.end());
}

//currently only supports +, -, * and /
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
            switch (t.opType)
            {
                case PLUS:
                case MINUS:
                case MULTIPLY:
                case DIVIDE:
                    followCountingRules(output, operators, t);
                    break;
                case PARENTHESE_LEFT:
                    operators.push_back(t);
                    break;
                //the operators that are inside the parentheses should be pushed all to output.
                case PARENTHESE_RIGHT: 
                    popTokensBeforeLeftParenthesis(output, operators);
                    break;
                default:
                    break;
            }
            break;
        case FUNCTION:
            switch (t.functionType)
            {
            case TO_POWER_OF:
                followCountingRules(output, operators, t);
                break;
            default:
                break;
            }
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
