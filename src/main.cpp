#include "main.h"


int main(){
    

    string input = "";
    getline(cin, input);
    

    const regex numberRegex("[0-9]");
    const regex operatorRegex("[\\+|\\-|\\*|\\/]");
    smatch match_number;
    smatch match_operator;
    for(int i = 0; i < input.size(); i++){
        string string_char = input.substr(i, 1);
        cout << string_char << "\n";
        bool confirmedNumber = regex_match(string_char, match_number, numberRegex);
        bool confirmedOperator = regex_match(string_char, match_operator, operatorRegex);
        if(confirmedNumber){
            cout << "is number!\n";
        }
        else if(confirmedOperator){
            cout << "is operator!\n";
        }
    }

    
    return 0;
}