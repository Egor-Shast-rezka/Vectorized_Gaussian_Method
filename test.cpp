/*
    Egor Shastin st129457@student.spbu.ru
    
    This is code for unit testing all classes by using Google Test
*/

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
