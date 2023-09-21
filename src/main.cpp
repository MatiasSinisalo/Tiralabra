#include "main.h"

int main(){
    string input = "";
    getline(cin, input);
    
    vector<token> tokens = getTokensFromInputString(input);

    vector<token> output = shuntingYard(tokens);

    debug_printTokens("final output stack now is: ", output);

    token finalResult = interpretFromRPN(output);
    cout << "the answer is: " << "\n";
    cout << finalResult.numberVal << "\n";
    return 0;
}