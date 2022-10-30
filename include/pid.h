/*! @file pid.h
 * defines pid controller namespace
 * Arduino PID library
 * https://github.com/br3ttb/Arduino-PID-Library
*/

// #pragma once  // only load libs once
#include <Arduino.h>

#define debug 0 // enable debug
#define ENABLE_HC 1 // enable hardcoded rules
// ERRORS AND RELATED SENSOR ARRAYS VALUES
float SOFT_ERROR = 1;              // 00011100
float SOFT_NEG_SR = 28;            // 00011100
float SOFT_POS_SR = 56;            // 00111000
float MIN_ERROR = 3;               // 00001100
float MIN_NEG_SR = 12;             // 00001100
float MIN_POS_SR = 48;             // 00110000
float THREE_MEDIUM_ERROR = 6;      // 00001110
float THREE_MEDIUM_NEG_SR = 14;    // 00001110
float THREE_MEDIUM_POS_SR = 112;   // 01110000
float MEDIUM_ERROR = 5;            // 00000110
float MEDIUM_NEG_SR = 6;           // 00000110
float MEDIUM_POS_SR = 96;          // 01100000
float THREE_EXTREME_ERROR = 9;     // 00000111
float THREE_EXTREME_NEG_SR = 7;    // 00000111
float THREE_EXTREME_POS_SR = 224;  // 11100000
float MAX_ERROR = 7;               // 00000011
float MAX_NEG_SR = 3;              // 00000011
float MAX_POS_SR = 192;            // 11000000
float EXTREME_ERROR = 4;           // 00000001
float EXTREME_NEG_SR = 1;          // 00000001
float EXTREME_POS_SR = 128;        // 10000000
float COMPLETE_ERROR = 10;         // 00001111
float COMPLETE_NEG_SR = 15;        // 00001111
float COMPLETE_POS_SR = 240;       // 11110000
// CORRECTIONS
float SOFT_CORRECTION = 2;            // 00011100
float MIN_CORRECTION = 5;             // 00001100
float THREE_MEDIUM_CORRECTION = 9;    // 00001110
float MEDIUM_CORRECTION = 19;         // 00000110
float THREE_EXTREME_CORRECTION = 30;  // 00000111
float MAX_CORRECTION = 32;            // 00000011
float EXTREME_CORRECTION = 32;        // 00000001
float COMPLETE_CORRECTION = 14;       // 00001111
// previous error
float e_prev = 0;
float last_control = 0;

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
          if(sensor_array == SOFT_POS_SR){
             // 00011100
            e_p = SOFT_CORRECTION;
          }
          else if(sensor_array == SOFT_NEG_SR) {
            //  00111000
            e_p = -SOFT_CORRECTION;
          }
          // remember from where extreme we scape
          if(last_control >= 30 and abs(e_p) <= MIN_ERROR) {
            e_p = last_control;
          }
          else if(last_control <= -30 and abs(e_p) <= MIN_ERROR){
            e_p = last_control;
          }
          // enable hardcoding
          if(ENABLE_HC == 1){
            // 00001100
            if(sensor_array == MIN_POS_SR) {
              e_p = MIN_CORRECTION;
            }
            else if(sensor_array == MIN_NEG_SR) {
              e_p = -MIN_CORRECTION;
            }
            // 00001110
            else if(sensor_array == THREE_MEDIUM_POS_SR) {
              e_p = THREE_MEDIUM_CORRECTION;
            }
            else if(sensor_array == THREE_MEDIUM_NEG_SR) {
              e_p = -THREE_MEDIUM_CORRECTION;
            }
            // 00000110
            else if(sensor_array == MEDIUM_POS_SR) {
              e_p = MEDIUM_CORRECTION;
            }
            else if(sensor_array == MEDIUM_NEG_SR) {
              e_p = -MEDIUM_CORRECTION;
            }
            // 00000111
            else if(sensor_array == THREE_EXTREME_POS_SR){
              e_p = THREE_EXTREME_CORRECTION;
            }
            else if(sensor_array == THREE_EXTREME_NEG_SR){
              e_p = -THREE_EXTREME_CORRECTION;
            }
            // 00000011
            else if(sensor_array == MAX_POS_SR){
              e_p = MAX_CORRECTION;
            }
            else if(sensor_array == MAX_NEG_SR){
              e_p = -MAX_CORRECTION;
            }
            // 00000001
            else if(sensor_array == EXTREME_POS_SR){
              e_p = EXTREME_CORRECTION;
            }
            else if(sensor_array == EXTREME_NEG_SR){
              e_p = -EXTREME_CORRECTION;
            }
            // 00001111
            else if(sensor_array == COMPLETE_POS_SR){
              e_p = COMPLETE_CORRECTION;
            }
            else if(sensor_array == COMPLETE_NEG_SR){
              e_p = -COMPLETE_CORRECTION;
            }
          }

      float control_u = e_p;
      if(debug){
        Serial.print("Current control_u (outside if) = ");
        Serial.println(control_u);
      }
      if(ENABLE_HC == 1){
        // when ENABLE_HC last_control = e_p
        float control_u = e_p;
        if(debug){
          Serial.print("Current control_u (inside if) = ");
          Serial.println(control_u);
        }
      }
      else{
        e_i += (e_p * dt) * K_i * 0;  // e_i(0) = 0
        e_d = (e_p - e_prev) * K_d; // dt
        float control_u = K_p*e_p
        + e_i
        + e_d;
        if(debug){
          Serial.print("Current control_u (inside else) = ");
          Serial.println(control_u);
        }
      }

      last_time = now; // last time
      last_control = control_u;
      //debug messages
      if(debug){
        Serial.print("Current e_p = ");
        Serial.println(e_p);
        Serial.print("Sensor measurement (final) = ");
        Serial.println(sensor_array, BIN);
        Serial.print("Control signal = ");
        Serial.println(control_u);
        Serial.print("Last control signal = ");
        Serial.println(last_control);
      }
      return control_u;
    }
    else return last_control;
      last_control = last_control;
  }
};
