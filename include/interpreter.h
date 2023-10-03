#include "tokenizer.h"
#include <math.h>
//reads as an input an token list in Reverse Polish Notation format 
//returns a single token containing the final evaluated value of the token list
token interpretFromRPN(const vector<token> tokensInRPN, tokenData &data);