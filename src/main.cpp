#include "main.h"


void runCalculator(const string input) {
    vector<token> tokens = getTokensFromInputString(input);
    debug_printTokens("input tokens are: ", tokens);

    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    token finalResult = interpretFromRPN(output);
    if (finalResult.type == NUMBER) {
        cout << "the answer is: " << "\n";
        cout << finalResult.numberVal << "\n";
    }
}


int main(){
    
    while (true) {
        string input = "";
        getline(cin, input);

        runCalculator(input);
    }
    return 0;
}