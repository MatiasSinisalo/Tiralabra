# Implementation document

# File Structure of the application:

- All source files used in the calculator are found in ./src
- All header files used in the calculator are found in ./include

- Testing files will be found under ./tests
- Test utilities will be found under ./tests/utilities

- Coverage will be found under ./coverage

- Documentiation will be found under ./documents

# Architecture of the Calculator:

The calculator is split into 3 phases:
1. Tokenizer will read the raw stdin from the user and return a list of tokens.
    - Implemented in tokenizer.cpp and tokenizer.h   
3. ShuntingYard will read a list of tokens and return an list of tokens in Reverse Polish Notation RPN using the Shunting Yard algorythm
   - Implemented in shuntingYard.cpp and shuntingYard.h   
4. Interpreter will read a list of tokens in RPN and return a single token containing the evaluated answer based on the input.
   - Implemented in interpreter.cpp and interpreter.h


## additional notes:
The tests of the application are dependent on the googletest testing libary.  
It will be automatically downloaded and compiled if the project is configured and built using CMAKE.  
