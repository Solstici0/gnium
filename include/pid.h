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
        Pid(float kp = 2, float ki = 0.0, float kd = 0.,
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
            //e_len = *(&Ta + 1) - Ta; // last pointer postion in
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
        //int e_len;  // error length

  float correction_signal(unsigned char sensor_array) {
    unsigned long now = millis();
    unsigned long t_change = (last_time - now);


    if (t_change >= dt){
      //Serial.write(0x69);
      // TODO (wis) obtain just one value for e_p
      //pid::Pid::e_p = sensor_array - pid::Pid::Ta;
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
        // some hardcoding :P
        e_prev = e_p;
          if(sensor_array == 56 or sensor_array == 28) {
            e_p = 0;
          }
          else if((e_prev == 7 or e_prev == 4) and sensor_array == 24){
            e_p = e_prev;

          }
          else if(e_p == 7 or e_p == 4) {
            e_p = 32/2;
          }
          else if(e_p == -7 or e_p == -4) {
            e_p = -32/2;
          }
          else if(e_p == 2) {
            e_p = 2/2;
          }
          else if(e_p == -2) {
            e_p = -2/2;
          }
          else if(e_p == 5) {
            e_p = 7/2;
          }
          else if(e_p == -5) {
            e_p = -7/2;
          }
      }
      

      //e_prev = e_p;
      e_i += (e_p * dt) * Ki * 0;  // e_i(0) = 0
      e_d = (e_p - e_prev) * Kd; // dt
      float control_u = Kp*e_p
       + e_i
       + e_d;
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
