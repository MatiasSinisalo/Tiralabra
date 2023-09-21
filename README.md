# Tiralabra Scientific Calculator

Programming language: c++20  
User interface: CLI, cin/cout  
[Weekly Reports](https://github.com/MatiasSinisalo/Tiralabra/tree/main/documents/weeklyreports)  

The goal is to build an scientific calculator using the Shunting yard Algorythm that calculates the value of a given mathematical argument.
This project is built as a part of my computer science bachelors studies in Helsinki Universitiy (fin: tietojenkäsittelytieteen kandidaatti (TKT)).

Planned features of the calculator:

1. basic mathematical operations using numerical values:
    - Addition
    - Substraction
    - Multiplication
    - Division
    - Square root
    - Exponent
2. Support for braces ()
3. Support for variables
    - a numerical value can be assigned to a variable
    - variables should support the same mathematical operations described above
4. Support for functions
    - user should be able to define a function f(x) and then be able to use it as a part of function g(x)
    - for example: f(x) = 2x and g(x) = f(x) + 3
# How to build the source:

## Using Cmake and make (for Unix)
    1. make sure you have the latest cmake and make installed
    2. clone the git repository
    3. open terminal at the repository root and type: 
        - cmake -G "Unix Makefiles" -B "./build"
        which will generate makefiles to folder ./build
    4. once generation is done navigate to ./build
    5. run make command:
        - make
    6. after make has finnished there should be two runnable files
        - TIRALABRA_SCIENTIFIC_CALCULATOR, which will run the program as it is.
        - TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS, which will run the tests for the project.
## Using Cmake and make (for windows)
    Install cmake and make for windows and follow the instructions listed above. 
    Main difference is that the output of make command will be .exe files.
