#include "ir_sensor.cpp"
#include "test_ir_sensor.h"
#include <unity.h>
void testSetup(void){
    ir_sensor::setup(69);
    TEST_ASSERT_EQUAL(69,ir_sensor::threshold);
}

void mainTestIrSensor(void){
    RUN_TEST(testSetup);
}