# Testing Document

## Branch and line coverage
Line and branch coverage report can be found under ./coverage as a set of html files.  
The main page for coverage is coverage.html.  

## Testing method
All tests are under ./tests.  

Tests are written in unit testing style where the 3 main parts (tokenizer, shuntingYard and interpreter) of the calculator are tested seperately from each other.  
The calculators parts are quite seperated from each other so the testing generally goes the following way:

0. (If needed mock state to simulate previus calculations, for example setting of variables or functions.)
1. Call the tested function with some test input.
2. Check the given output of the function and its side effects on state.


## Running the tests and generating line coverage report (Unix)

1. Generate project files with cmake to ./build/
2. Navigate to the generated project files folder.
3. Run tests with coverage tracking "ctest -T test -T coverage".
4. Navigate to the root of the project.
5. Generate html report of coverage with gcovr: "gcovr --html-details ./coverage/coverage.html".
