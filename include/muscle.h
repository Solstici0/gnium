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
#define MIN_MICROS_MUSCLE 880  //544
#define MAX_MICROS_MUSCLE 2080
// In our case, we know from experiments:
// - max_width = 2.12 ms = 2120 us (MAX MICROS)
// - min_width = 0.88 ms = 880 us (MIN MICROS)
#define MUSCLE_PIN_ANGLE PB14  // TODO: check!

#define debug 1 // enable debug
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
                                  MIN_MICROS_MUSCLE,
                                  MAX_MICROS_MUSCLE);
    if (MUSCLE_MOTOR != -1) {
      if(debug){
        Serial.println("Muscle motor initialization succeeds!");
        Serial.println(MUSCLE_MOTOR);
      }
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
      if(debug){
        Serial.println("Muscle velocity = ");
        Serial.println(vel_in_deg);
      }
    }
    }
  void test_routine(void){
    int init_vel = 90;
    int vel = init_vel;
    int max_vel = 110;
    int min_vel = 70;
    while(1){
    // forward
    for(vel = init_vel; vel <= max_vel; vel+=1) {
      set_vel(vel);
      delay(200);
    }
    for(vel = max_vel; vel >= min_vel; vel-=1) {
      set_vel(vel);
      delay(200);
    }
    for(vel = min_vel; vel <= init_vel; vel+=1) {
      set_vel(vel);
      delay(200);
    }
    }
  }
  void test_vel(float testing_vel){
    int init_vel = 90;
    while(1){
    int vel = init_vel;
    int n = 0;
    if(testing_vel > init_vel){
      for(vel=init_vel; vel<=testing_vel; vel+=1){
        if(vel==testing_vel){
          for(n=0; n<=200; ++n){
          set_vel(vel);
          delay(50);
          }
        }
        else{
          set_vel(vel);
          delay(50);
        }
      }
    }
    else if(testing_vel <= init_vel){
      for(vel=init_vel; vel>=testing_vel; vel-=1){
        if(vel==testing_vel){
          for(n=0; n<=200; ++n){
          set_vel(vel);
          delay(50);
          }
        }
        else{
          set_vel(vel);
          delay(50);
        }
      }
    }
    delay(2000);
    }
  }
  void test_forward_vel(float steady_vel) {
    float init_vel = 90;
    float max_vel = 100;
    int n = 0;
    while(1){
      float vel = init_vel;
      for(vel=init_vel; vel<=max_vel; vel+=1) {
      set_vel(vel);
      delay(50);
      }
      for(vel=max_vel; vel>=steady_vel; vel-=1) {
      set_vel(vel);
      delay(50);
      }
      for(n=0; n<=40; ++n){
      set_vel(vel);
      delay(50);
      }
    }
  }
}
