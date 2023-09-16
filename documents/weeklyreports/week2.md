# Week 2 report
## Hours used: 13h

## Progress of the project:

Cmake, testing(googletest) and line coverage(gcovr) were configured.  
The program now accepts inputs of single digits and of operations +, - and * in infix form and outputs an tokenlist created by shunting yard algorythm. 
Also some testing with googletest has been written to test the program behauvior.   

## Lessons learned and challenges encountered:
Configuring CMake, googletest and line coverage to work took me a while, but the documentation helped and eventually the configs worked.
Sources used for the configuring:
- https://cmake.org/cmake/help/latest/guide/tutorial/
- https://github.com/google/googletest/tree/main/googletest
- https://gcovr.com/en/stable/installation.html
- http://google.github.io/googletest/primer.html
- https://coderefinery.github.io/cmake-workshop/fetch-content/

Understanding the shunting yard algorythm and especially the Reverse Polish Notation was fun and interesting. 
I maybe spent too much time trying to figure the algorythm out by experimentation, but I think it helped me understand the algorythm better.
Sources used for the algorythm: 
- https://en.wikipedia.org/wiki/Shunting_yard_algorithm
- https://en.wikipedia.org/wiki/Reverse_Polish_notation 

During the development I should have started testing a lot sooner. 
Testing would have prevented me making some basic errors, suchs as combining the output and operators vectors incorrectly. 
I made the decision of using vectors like stacks instead of stacks in order to make debug printing a little more convinient, 
but I should have tested that I actually used the vectors like stacks and not vectors.

## Goal for the next week:
- Support for divisions as well as braces.
- Make the calculator give the final calculation result back instead of the token list.
- Improved testing for more varied inputs.
- maybe add POWER(X, Y) function if there is time.
