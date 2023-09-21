#include "tokenizer.h"

vector<token> getTokensFromInputString(const string input) {
    vector<token> tokens;
    const regex numberRegex("[0-9]");
    const regex operatorRegex("[\\+|\\-|\\*|\\/|(|)]");
    smatch matchNumber;
    smatch matchOperator;
    for (int i = 0; i < input.size(); i++) {
        string string_char = input.substr(i, 1);
        
        bool confirmedNumber = regex_match(string_char, matchNumber, numberRegex);
        bool confirmedOperator = regex_match(string_char, matchOperator, operatorRegex);

        if (confirmedNumber) {
            
            tokens.push_back({
                .type = NUMBER,
                .opType = NONE,
                .numberVal = stoi(string_char)
            });
        }
        else if (confirmedOperator) {
            
            token newToken{
                .type = OPERATOR,
            };
            if (string_char == "+")
            {
                newToken.opType = PLUS;
            }
            else if (string_char == "-")
            {
                newToken.opType = MINUS;
            }
            else if (string_char == "/")
            {
                newToken.opType = DIVIDE;
            }
            else if (string_char == "*")
            {
                newToken.opType = MULTIPLY;
            }
            else if (string_char == "(")
            {
                newToken.opType = PARENTHESE_LEFT;
            }
             else if (string_char == ")")
            {
                newToken.opType = PARENTHESE_RIGHT;
            }
            tokens.push_back(newToken);
        }
    }

    return tokens;
}

void debug_printTokens(const string extraMsg, const vector<token> tokens) {
    #ifdef DEBUG_PRINTS
        cout << extraMsg << "\n";
        cout << "[";
        for (const token& t : tokens) {
            cout << tokenTypeToString[t.type] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << ", ";
        }
        cout << "]\n";
    #endif
}
