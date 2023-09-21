cmake_minimum_required(VERSION 3.22.1)
project (TIRALABRA_SCIENTIFIC_CALCULATOR)
file(GLOB sources
     "include/*.h"
     "src/*.cpp"
)
add_executable(TIRALABRA_SCIENTIFIC_CALCULATOR ${sources})
target_include_directories(TIRALABRA_SCIENTIFIC_CALCULATOR PUBLIC ./include)

project(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB sources_test
     "./tests/*.cpp"
     "./src/tokenizer.cpp"
     "./src/shuntingYard.cpp"
     "./src/interpreter.cpp"
)
add_executable(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS ${sources_test})
target_include_directories(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS PUBLIC ./include)
target_link_libraries(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS PUBLIC gtest_main)

target_compile_options(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS PUBLIC --coverage)
target_link_options(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS PUBLIC --coverage)

include(GoogleTest)
include(CTest)




gtest_discover_tests(TIRALABRA_SCIENTIFIC_CALCULATOR_TESTS)