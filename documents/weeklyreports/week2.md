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
