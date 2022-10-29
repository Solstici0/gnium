/**
 * @file muscle.h
 * @brief Function to interact with muscle motor
 * @version 0.1
 * @date 2022-10-12
 * STM32 servo library
 * https://github.com/khoih-prog/STM32_ISR_Servo
 */
#define TIMER_INTERRUPT_DEBUG 0
#define ISR_SERVO_DEBUG 0

#include "STM32_ISR_Servo.h"

#define BLUE_PILL //which microcontroller is running the code
#ifdef BLUE_PILL
// Default is TIMER_SERVO (TIM7 for many boards)
#define USE_STM32_TIMER_NO TIMER_SERVO
// Published values for SG90 servos; adjust if needed
#define MIN_MICROS 880  //544
#define MAX_MICROS 2120
// In our case, we know from experiments:
// - max_width = 2.12 ms = 2120 us (MAX MICROS)
// - min_width = 0.88 ms = 880 us (MIN MICROS)
#define MUSCLE_PIN_ANGLE PB14  // TODO: check!

int MUSCLE_MOTOR = -1;

#elif TEENSY35
#endif

namespace muscle{
  /**
   * @brief
   * @param
   */
  void setup(){
   /**
    * @brief initialize pins for muscle motor
    * @params pin numbers
    */
    STM32_ISR_Servos.useTimer(USE_STM32_TIMER_NO);
    MUSCLE_MOTOR = STM32_ISR_Servos.setupServo(
                                  MUSCLE_PIN_ANGLE,
                                  MIN_MICROS,
                                  MAX_MICROS);
    if (MUSCLE_MOTOR != -1) {
    Serial.println("Muscle motor initialization succeeds!");
    Serial.println(MUSCLE_MOTOR);
    }
  }

  void set_vel(float vel_in_deg){
   /**
    * @brief set new velocity
    * @param vel_in_deg to the muscle motor
    * forward velocity for vel_in_deg > 90
    */
    if (MUSCLE_MOTOR != -1) {
      STM32_ISR_Servos.setPosition(MUSCLE_MOTOR,
                                 vel_in_deg);
    }
    }
  void test_routine(void){
    int vel = 90;
    while(1){
    // forward
    for(vel = 90; vel <= 120; vel+=1) {
      set_vel(vel);
      delay(200);
    }
    for(vel = 120; vel >= 60; vel-=1) {
      set_vel(vel);
      delay(200);
    }
    for(vel = 60; vel <= 90; vel+=1) {
      set_vel(vel);
      delay(200);
    }
    }
  }
}
