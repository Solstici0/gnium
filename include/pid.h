/*! @file pid.h
 * defines pid controller namespace
 * Arduino PID library
 * https://github.com/br3ttb/Arduino-PID-Library
*/

// #pragma once  // only load libs once
#include <Arduino.h>

namespace pid {
  class Pid;
}

class pid::Pid {
    /*! @class Pid
    * creates pid object
    */
    public:
        // Constructor
        Pid(float kp = 10., float ki = 0., float kd = 0.,
            //int target_array[8] = {0, 0}) {
            unsigned char target_array = 24) {
            Kp = kp;
            ki = ki;
            Kd = kd;
            //for(i = 0; i < 8; i++){
            //  Ta[i] = target_array[i];
            //}
            Ta = target_array;
            e_prev = 0; // TODO: in the future this variables should be injected
            dt = 20; // sample time for changing controlled vars
            e_p = 0;
            e_i = 0;
            e_d = 0;
            last_time = 0;
            last_control = 0;
            e_len = *(&Ta + 1) - Ta; // last pointer postion in
                                     // memory, minus first pointer
                                     // position.
        }
    public:
        float Kp; // proportional constant
        float Ki; // integral constant
        float Kd; // derivative constant
        unsigned char Ta; // target array (perfect position over trace)
        float e_prev; // previous error
        int dt;  // delta t
        float e_p;  // proportional error
        float e_i;  // integral error
        float e_d;  // derivative error
        int last_time;
        int last_control;  // last control signal
        int e_len;  // error length

  float correction_signal(unsigned char sensor_array) {
    unsigned long now = millis();
    unsigned long t_change = (pid::Pid::last_time - now);
    if (t_change >=dt){
      // TODO (wis) obtain just one value for e_p
      //pid::Pid::e_p = sensor_array - pid::Pid::Ta;
      for(int i = 0; i < e_len; i++) {
          // we can ponderate the substraction below 
          //pid::Pid::e_p += pid::Pid::Ta[i] - sensor_array[i];
          if (i < 4){
            pid::Pid::e_p += (pid::Pid::Ta>>i - sensor_array>>i)*(i-4);
          }
          else{
            pid::Pid::e_p += (pid::Pid::Ta>>i - sensor_array>>i)*(i-3);
          }
      }
      
      
      pid::Pid::e_i += pid::Pid::e_p * dt;  // e_i(0) = 0
      pid::Pid::e_d = (pid::Pid::e_p - pid::Pid::e_prev); // dt
      float control_u = pid::Pid::Kp*e_p
      + pid::Pid::Ki*e_i
      + pid::Pid::Kd*e_d;
      pid::Pid::e_prev = e_p;
      pid::Pid::last_time = now; // last time
      pid::Pid::last_control = control_u;
      return control_u;
    }
    else return pid::Pid::last_control;
  }
};
