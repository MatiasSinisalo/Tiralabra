# Week 5 report
# Hours used: 11.5


## Progress of the application:
Application now supports variables and started work on custom defined functions. 

A regression sadly was introduced for input checking, the application no longer gives a nice error message for using a function without ( .  

Variables can be declared with VARIABLE(variableName,value) and a function can be declared with FUNCTION(functionName,expression)  
Function currently takes no argumments but variables can be used in a following way in functions:  
![capture_functions](https://github.com/MatiasSinisalo/Tiralabra/assets/50097749/8d53b6c7-bb69-4d92-bf5a-72e1bbb37b27)

## Problems encountered and lessons learned

Functions do not currently completely work as part of expressions, and there are no unit tests for the implementation of functions. It was a bit tricky to get the interpreter to not evaluate the expression of a function into a single value when it was declared. 

At this point of the project the lack of proper incorrect input checking is starting to be an issue as well. I should have prioritized it more. It is very easy to get the program to crash and the errors given for incorrect inputs are also very bad.

## goals for the next week:
- Finnish implementing of custom functions
- Actual incorrect input checking with helpful messages.
- More documentation for the project.
