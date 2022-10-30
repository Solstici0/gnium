/*! @file pid.h
 * defines pid controller namespace
 * Arduino PID library
 * https://github.com/br3ttb/Arduino-PID-Library
*/

// #pragma once  // only load libs once
#include <Arduino.h>

#define ENABLE_HC 1 // enable hardcoded rules
float MIN_ERROR = 1;            // 00001100
float MEDIUM_ERROR = 5;         // 00000110
float MAX_ERROR = 7;            // 00000011
float EXTREME_ERROR = 4;        // 00000001
float THREE_EXTREME_ERROR = 9;  // 00000111
float MIN_CORRECTION = 2;
float MEDIUM_CORRECTION = 7;
float MAX_CORRECTION = 32;
float EXTREME_CORRECTION = 32;
float THREE_EXTREME_CORRECTION = 32;

namespace pid {
  class Pid;
}

class pid::Pid {
    /*! @class Pid
    * creates pid object
    */
    public:
        // Constructor
        Pid(float k_p = 2, float k_i = 0.0, float k_d = 0.,
            unsigned char target_array = 24) {
            K_p = k_p;
            k_i = k_i;
            K_d = k_d;
            Ta = target_array;
            e_prev = 0.; // TODO: in the future this variables should be injected
            dt = 20; // sample time for changing controlled vars
            e_p = 0.;
            e_i = 0.;
            e_d = 0.;
            last_time = 0;
            last_control = 0.;
            control_u = 0.;
        }
    public:
        float K_p; // proportional constant
        float K_i; // integral constant
        float K_d; // derivative constant
        unsigned char Ta; // target array (perfect position over trace)
        float e_prev; // previous error
        int dt;  // delta t
        float e_p;  // proportional error
        float e_i;  // integral error
        float e_d;  // derivative error
        int last_time;
        float last_control;  // last control signal
        float control_u;  // initial control signal

  float correction_signal(unsigned char sensor_array) {
    // time counter
    unsigned long now = millis();
    unsigned long t_change = (last_time - now);

    if (t_change >= dt){
      //Serial.write(0x69);
      e_p = 0;
      for(int i = 0; i < 8; i++) {
          // we can ponderate the substraction below 
          //pid::Pid::e_p += pid::Pid::Ta[i] - sensor_array[i];
          if (i < 4){
            e_p += (((Ta>>i)&1) - ((sensor_array>>i)&1))*(4-i);
          }
          else{
            e_p += (((Ta>>i)&1) - ((sensor_array>>i)&1))*(3-i);
          }
        }
          // save previous error signal
          e_prev = e_p;
          // some hardcoding :P
          // disable very soft correction
          if(sensor_array == 56 or sensor_array == 28) {
            //  00111000 or 00011100
            e_p = 0;
          }
          // remember from where extreme we scape
          if(last_control >= 30 and e_p == 0) {
            e_p = last_control;
          }
          else if(last_control <= -30 and e_p == 0){
            e_p = last_control;
          }
          // enable hardcoding
          if(ENABLE_HC == 1){
            if(e_p == MIN_ERROR) {
              e_p = MIN_CORRECTION;
            }
            else if(e_p == -MIN_ERROR) {
              e_p = -MIN_CORRECTION;
            }
            else if(e_p == MEDIUM_ERROR) {
              e_p = MEDIUM_CORRECTION;
            }
            else if(e_p == -MEDIUM_ERROR) {
              e_p = -MEDIUM_CORRECTION;
            }
            else if(e_p == MAX_ERROR or e_p == EXTREME_ERROR
               or e_p == THREE_EXTREME_ERROR) {
              e_p = MAX_CORRECTION;
            }
            else if(e_p == -MAX_ERROR or e_p == -EXTREME_ERROR
                    or e_p == THREE_EXTREME_ERROR) {
              e_p = -MAX_CORRECTION;
            }
          }
      
      if(ENABLE_HC == 1){
        // when ENABLE_HC last_control = e_p
        float control_u = e_p;
      }
      else{
        e_i += (e_p * dt) * K_i;  // e_i(0) = 0
        e_d = (e_p - e_prev) * K_d; // dt
        float control_u = K_p*e_p
        + e_i
        + e_d;
      }

      last_time = now; // last time
      last_control = control_u;
      //debug messages
      // Serial.print("Sensor measurement = ");
      // Serial.println(sensor_array, BIN);
      // Serial.print("Control signal = ");
      // Serial.println(control_u);
      return control_u;
    }
    else return last_control;
  }
};
