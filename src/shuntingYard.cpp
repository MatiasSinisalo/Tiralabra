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

bool beforeIsHigherPrecedence(vector<token>& output, vector<token>& operators) {
    if (operators.size() > 0) {
        token operatorBefore = operators.back();
        switch (operatorBefore.opType)
        {
        case MULTIPLY:
            return true;
            break;

        default:
            return false;
            break;
        }
    }
    return false;
}

void followCountingRules(vector<token>& output, vector<token>& operators) {
    if (beforeIsHigherPrecedence(output, operators) || beforeIsLeftAssociative(output, operators))
    {
        token operatorBefore = operators.back();
        output.push_back(operatorBefore);
        operators.pop_back();
    }
}

//currently only supports + and -
//output should be Reverse Polish notation RPN
vector<token> shuntingYard(const vector<token> tokens) {
    vector<token> output;
    vector<token> operators;
    for (const token& t : tokens) {
        switch (t.tokenType)
        {
        case NUMBER:
            output.push_back(t);
            break;
        case OPERATOR:
            switch (t.opType)
            {
            case PLUS:
                followCountingRules(output, operators);
                operators.push_back(t);
                break;
            case MINUS:
                followCountingRules(output, operators);
                operators.push_back(t);
                break;
            case MULTIPLY:
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
