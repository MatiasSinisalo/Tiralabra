cmake_minimum_required(VERSION 3.22.1)


project (TIRALABRA_SCIENTIFIC_CALCULATOR_LIB LANGUAGES CXX)
file(GLOB sources_lib
     "./lib/custom_libary/include/*.h"
     "./lib/custom_libary/src/*.cpp"
)
add_library(TIRALABRA_SCIENTIFIC_CALCULATOR_LIB  SHARED ${sources_lib})
target_include_directories(TIRALABRA_SCIENTIFIC_CALCULATOR_LIB PUBLIC ./lib/custom_libary/include/)

project (TIRALABRA_SCIENTIFIC_CALCULATOR)
file(GLOB sources
     "include/*.h"
     "src/*.cpp"
)
add_executable(TIRALABRA_SCIENTIFIC_CALCULATOR ${sources})
target_include_directories(TIRALABRA_SCIENTIFIC_CALCULATOR PUBLIC ./include)
target_link_libraries(TIRALABRA_SCIENTIFIC_CALCULATOR PRIVATE TIRALABRA_SCIENTIFIC_CALCULATOR_LIB)