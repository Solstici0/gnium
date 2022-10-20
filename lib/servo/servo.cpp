//#include "servo.h"
//#include "STM32_ISR_Servo.h"
//
//#define BLUE_PILL //which microcontroller is running the code
//#ifdef BLUE_PILL
//// Default is TIMER_SERVO (TIM7 for many boards)
//#define USE_STM32_TIMER_NO TIMER_SERVO
//// Published values for SG90 servos; adjust if needed
//#define MIN_MICROS 800  //544
//#define MAX_MICROS 2450
//
//#define SERVO_PIN_ANGLE D1
//#elif TEENSY35
//#endif
//
//namespace servo{
//  void setup(){
//    STM32_ISR_Servos.useTimer(USE_STM32_TIMER_NO);
//    int ANGLE_SERVO = STM32_ISR_Servos.setupServo(
//                                  SERVO_PIN_ANGLE,
//                                  MIN_MICROS,
//                                  MAX_MICROS);
//  }
//
//  void set_angle(float angle_correction){
//    // TODO (wis) send information to servo
//    float new_angle = base_angle + angle_correction
//    STM32_ISR_Servos.setPosition(ANGLE_SERVO,
//                                 new_angle);
//  }
//}
