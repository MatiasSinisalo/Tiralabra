#include "shuntingYard.h"

bool beforeIsLeftAssociative(vector<token>& output, vector<token>& operators) {
    if (operators.size() > 0) {
        token operatorBefore = operators.back();
        switch (operatorBefore.type)
        {
      
        case OP_MINUS: //minus is only left associative
        case OP_PLUS: //plus is both left and right associative so it must also be handled
        case OP_DIVIDE: //divide is left associative
        case OP_MULTIPLY: // multiplty is left and right
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
        if(operatorBefore.type == OP_MULTIPLY || operatorBefore.type == OP_DIVIDE){
            if(compareTo.type == OP_MINUS || compareTo.type == OP_PLUS){
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
        if(beforeToken.type == compareTo.type){
            return true;
        }
        else if(beforeToken.type == OP_MINUS && compareTo.type == OP_PLUS){
            return true;
        }
        else if(beforeToken.type == OP_PLUS && compareTo.type == OP_MINUS){
            return true;
        }
        else if(beforeToken.type == OP_MULTIPLY && compareTo.type == OP_DIVIDE){
            return true;
        }
        else if(beforeToken.type == OP_DIVIDE && compareTo.type == OP_MULTIPLY){
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
       
        if(source[i].type == PARENTHESE_LEFT){
            stoppingIndex = i;
            break;
        }
        
        target.push_back(source[i]);
    }
    source.erase(source.begin()+ stoppingIndex, source.end());

    //in case of FUNCTION(A, B), the program should push FUNCTION to target to maintain the order of operations correctly
    if (source.size() > 0 && source.back().type == FUNC_POWER) {
        token tokenToMove = source.back();
        target.push_back(tokenToMove);
        source.pop_back();
    }
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
                operators.push_back(t);
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
