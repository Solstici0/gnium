/**
 * @file test_main.cpp
 * @author Felipe Guajardo (felipe.guajardo@solstic.io)
 * @brief Here is the main method of the test suite, it should include all the other test files and a method for each 
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <unity.h>
#include "test_gnium_pid_pwm.h"
#include "test_ir_sensor.h"

int main(void){
    UNITY_BEGIN();
    mainTestGniumPidPwm();
    mainTestIrSensor();
    UNITY_END();
}