#include "main.h"


//just a test for the sake of it....
//should probably use an c++ interface to be honest
token doFunctionEvaluation(token A, token B){
    cout << "this works! \n";
    return {};
};

token doFunctionEvaluationB(token A, token B){
    cout << "yet another function evaluation\n";
    return {};
};

struct evalFunc{
    token (*eval) (token A, token B);
};
vector<std::pair<uint64_t, evalFunc>> functions_test = {
    {
        (uint64_t)0,
        {
            .eval = doFunctionEvaluation
        }
    },
    {
        (uint64_t)1,
        {
            .eval = doFunctionEvaluationB
        }
    }
};



int main(){
    functions_test[0].second.eval({}, {});
     functions_test[1].second.eval({}, {});
    string input = "";
    getline(cin, input);
    
    vector<token> tokens = getTokensFromInputString(input);
    debug_printTokens("input tokens are: ", tokens);

    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    token finalResult = interpretFromRPN(output);
    cout << "the answer is: " << "\n";
    cout << finalResult.numberVal << "\n";
    return 0;
}