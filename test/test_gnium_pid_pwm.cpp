/*! @file test_gnium_pid_pwm
Test gnium creation and methodis, pid and pwd functions
*/

#include <unity.h>
#include <gnium.h>
#include <pid.h>
#include <pwm.h>
//#include <stdio.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_example(void) {
    TEST_ASSERT_EQUAL(0, 0);
}


void test_gnium_creation_succeed(void) {
    // TODO improve testing scheme
    gnium::Gnium gnium = gnium::Gnium(0, 0, 0);
    gnium::Gnium gnium2 = gnium::Gnium(1, 0, 0);
    gnium::Gnium gnium3 = gnium::Gnium(0, 1, 0);
    gnium::Gnium gnium4 = gnium::Gnium(1, 1, 0);
}

int main(void)
{
    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_example);
    RUN_TEST(test_gnium_creation_succeed);
    UNITY_END(); // stop unit testing
}
