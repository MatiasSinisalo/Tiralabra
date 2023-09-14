#include <gtest/gtest.h>
#include "hello.h"
#include <iostream>
// Demonstrate some basic assertions.
TEST(HelloTest, sayHelloPrintsCorrectly) {
    testing::internal::CaptureStdout();
        say_hello();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output.compare("the program says hello!\n"), 0);
}

TEST(HelloTest, thisHelloTestShouldFail) {
    testing::internal::CaptureStdout();
        say_hello();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output.compare("this should fail!\n"), 0) << "this failure is expected and for testing testing";
}