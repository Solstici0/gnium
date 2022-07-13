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
    TEST_ASSERT_EQUAL(gnium.Mode, 0);
    TEST_ASSERT_EQUAL(gnium.Type, 0);
    TEST_ASSERT_EQUAL(gnium.Lap_n, 0);
    TEST_ASSERT_EQUAL(gnium.Start_detected, false);
    TEST_ASSERT_EQUAL(gnium.End_detected, false);
    gnium::Gnium gnium2 = gnium::Gnium(1, 0, 0);
    gnium::Gnium gnium3 = gnium::Gnium(0, 1, 0);
    gnium::Gnium gnium4 = gnium::Gnium(1, 1, 0);
}

void test_gnium_reset_start_and_end_succeed(void) {
    gnium::Gnium gnium = gnium::Gnium(0,0,0);
    // set them to 1
    gnium.Start_detected = 1;
    gnium.End_detected = 1;
    TEST_ASSERT_EQUAL(true, gnium.Start_detected);
    TEST_ASSERT_EQUAL(true, gnium.End_detected);

    // test reset function works
    gnium.reset_start_and_end();
    TEST_ASSERT_EQUAL(false, gnium.Start_detected);
    TEST_ASSERT_EQUAL(false, gnium.End_detected);
}

void test_gnium_run_lap_succeed(void) {
    gnium::Gnium gnium = gnium::Gnium(0,0,0);
    int fail = 0;
    fail = gnium.run_lap(0);  // this will run forever!
    TEST_ASSERT_EQUAL(1, fail);
}
int main(void)
{
    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_example);
    RUN_TEST(test_gnium_creation_succeed);
    RUN_TEST(test_gnium_reset_start_and_end_succeed);
    //RUN_TEST(test_gnium_run_lap_succeed);
    UNITY_END(); // stop unit testing
}
