cmake_minimum_required(VERSION 3.22.1)
project (TIRALABRA_SCIENTIFIC_CALCULATOR)

include_directories(./include)
file(GLOB sources
     "include/*.h"
     "src/*.cpp"
)

add_executable(TIRALABRA_SCIENTIFIC_CALCULATOR ${sources})