/*
simple test experiment
*/

#include <unity.h>
//#include <stdio.h>

void test_example(void) {
    TEST_ASSERT_EQUAL(0, 0);
}

void test_example2(void) {
    TEST_ASSERT_EQUAL(0, 1);
}

int main(void)
{
    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_example);
    RUN_TEST(test_example2);
    UNITY_END(); // stop unit testing
}
