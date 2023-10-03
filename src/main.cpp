#include "main.h"


void runCalculator(const string input, tokenData &data) {
    vector<token> tokens = getTokensFromInputString(input, data);
    debug_printTokens("input tokens are: ", tokens);

    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    token finalResult = interpretFromRPN(output);
    if (finalResult.type == NUMBER) {
        cout << "the answer is: " << "\n";
        cout << finalResult.value << "\n";
    }
}


int main(){
    tokenData tokensData = {};

    while (true) {
        string input = "";
        getline(cin, input);

        runCalculator(input, tokensData);
    }
    return 0;
}