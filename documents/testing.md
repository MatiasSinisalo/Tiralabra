# Testing Document

## Branch and line coverage
Line and branch coverage report can be found under ./coverage as a set of html files.  
The main page for coverage is coverage.html.  

## Testing method
Tests are written in unit testing style where the 3 main parts (tokenizer, shuntingYard and interpreter) of the calculator are tested seperately from each other.  
The calculators parts are quite seperated from each other so the testing generally goes the following way:

0. (If needed mock state to simulate previus calculations, for example setting of variables or functions) 
1. Call the tested function with some test input
2. Check the given output of the function and its side effects on state.


## Running the tests

