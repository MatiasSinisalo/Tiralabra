#include "tokenizer.h"

vector<token> getTokensFromInputString(const string input) {
    vector<token> tokens;
    const regex numberRegex("[0-9]");
    const regex operatorRegex("[\\+|\\-|\\*|\\/]");
    smatch matchNumber;
    smatch matchOperator;
    for (int i = 0; i < input.size(); i++) {
        string string_char = input.substr(i, 1);
        cout << string_char << "\n";
        bool confirmedNumber = regex_match(string_char, matchNumber, numberRegex);
        bool confirmedOperator = regex_match(string_char, matchOperator, operatorRegex);

        if (confirmedNumber) {
            cout << "is number!\n";
            tokens.push_back({
                .type = NUMBER,
                .opType = NONE,
                .numberVal = stoi(string_char)
            });
        }
        else if (confirmedOperator) {
            cout << "is operator!\n";
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
            tokens.push_back(newToken);
        }
    }

    return tokens;
}

void debug_printTokens(const string extraMsg, const vector<token> tokens) {
    cout << extraMsg << "\n";
    cout << "[";
    for (const token& t : tokens) {
        cout << tokenTypeToString[t.type] << " " << operatorTypeToString[t.opType] << " " << t.numberVal << ", ";
    }
    cout << "]\n";
}
