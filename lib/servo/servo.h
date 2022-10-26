/**
 * @file servo.h
 * @brief Function to interact with servo motor
 * @version 0.1
 * @date 2022-10-12
 * STM32 servo library
 * https://github.com/khoih-prog/STM32_ISR_Servo
 */
#include "servo.h"
#include "STM32_ISR_Servo.h"

#define BLUE_PILL //which microcontroller is running the code
#ifdef BLUE_PILL
// Default is TIMER_SERVO (TIM7 for many boards)
#define USE_STM32_TIMER_NO TIMER_SERVO
// Published values for SG90 servos; adjust if needed
#define MIN_MICROS 800  //544
#define MAX_MICROS 2450

#define SERVO_PIN_ANGLE D1
#elif TEENSY35
#endif

namespace servo{
  /**
   * @brief
   * @param
   */
  void setup(){
   /**
    * @brief initializa pins for servo motor
    * @params pin numbers
    */
    STM32_ISR_Servos.useTimer(USE_STM32_TIMER_NO);
    int ANGLE_SERVO = STM32_ISR_Servos.setupServo(
                                  SERVO_PIN_ANGLE,
                                  MIN_MICROS,
                                  MAX_MICROS);
  }

  void set_angle(float angle_correction){
   /**
    * @brief set new angle given information from pid
    * @param angle_correction given by pid
    */
    STM32_ISR_Servos.setPosition(ANGLE_SERVO,
                                 angle_correction);
  }
}
