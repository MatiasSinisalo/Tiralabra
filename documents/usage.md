## Using the calculator:
Currently the calculator accepts calculations in latin infix notation without spaces.
The input can contain positive integer numbers such as 1, 2, 200, 500, .. etc.

The input can contain '(' and ')' as well to influence the order of operations.
for example: 2*(1+2) will return 6.

User can define Variables with VARIABLE(variableName,value).  

User can define functions with FUNCTION(functionName,expression).  
Functions can contain variables and other functions as long as those variables/functions are defined before the function is defined:

1. VARIABLE(x,10)
2. FUNCTION(foo,2*x)
3. (typing foo() will return 20)


A function can contain another function as well:

1. VARIABLE(x,20)
2. FUNCTION(foo,2*x)
3. FUNCTION(bar,10*foo())
4. (typing bar() will return 400)

## Additional example inputs:

Calculating 2^4: POWER(2,4)

Calculating square root of 16: SQRT(16)
