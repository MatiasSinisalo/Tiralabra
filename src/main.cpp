#include "main.h"


//just a test for the sake of experimentation
struct evalFunc{
    vector<token> functionAsNormalInfixNotation;
};

//this way of implementig functions 
//could possibly allow for easy defining of new functions in runtime by the user...
vector<std::pair<uint64_t, evalFunc>> functions_test = {
    {
        (uint64_t)0,
        {
            .functionAsNormalInfixNotation = {
                {

                    .type = NUMBER, 
                    .numberVal = 1,
                },
                {

                    .type = OPERATOR, 
                    .opType = PLUS,
                },
                {

                    .type = NUMBER, 
                    .numberVal = 1,
                },
            }
        }
    },
};



int main(){
    
    /*
    string input = "";
    getline(cin, input);
    
    vector<token> tokens = getTokensFromInputString(input);
    debug_printTokens("input tokens are: ", tokens);
    */

    vector<token> tokens = functions_test[0].second.functionAsNormalInfixNotation;
    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    token finalResult = interpretFromRPN(output);
    cout << "the answer is: " << "\n";
    cout << finalResult.numberVal << "\n";
    return 0;
}