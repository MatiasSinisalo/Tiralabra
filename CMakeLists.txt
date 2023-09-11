cmake_minimum_required(VERSION 3.27.4)
project (TIRALABRA_SCIENTIFIC_CALCULATOR)


set(SOURCES ./src/main.cpp ./src/hello.cpp ./headers/main.h ./headers/hello.h)
add_executable(TIRALABRA_SCIENTIFIC_CALCULATOR ${SOURCES})
add_subdirectory(./src)
add_subdirectory(./headers)