/*! @file pid.h
 * defines pid controller namespace
 * Arduino PID library
 * https://github.com/br3ttb/Arduino-PID-Library
*/

// #pragma once  // only load libs once
#include <Arduino.h>
//#include <cmath>
#include <math.h>

#define debug 0 // enable debug
#define ENABLE_HC 0 // enable hardcoded rules
//#define PI 3.141592654

int straight = 0;
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
float COMPLETE_NEG_SR = 15;        // 0000111
float COMPLETE_POS_SR = 240;       // 11110000
// CORRECTIONS
float SOFT_CORRECTION = 2;            // 00011100
float MIN_CORRECTION = 5;             // 00001100
float THREE_MEDIUM_CORRECTION = 9;    // 00001110
float MEDIUM_CORRECTION = 17;         // 00000110
float THREE_EXTREME_CORRECTION = 25;  // 00000111
float MAX_CORRECTION = 30;            // 00000011
float EXTREME_CORRECTION = 32;        // 00000001
float COMPLETE_CORRECTION = 13;       // 00001111
// previous error
float e_prev = 0;
float last_control = 0;
float last_control_v = 0;
float control_u = 0;
//float last_time = 0;
// relevant distances
float OFFSET_DIST = -1.875;
float BETWEEN_SENSOR_DIST = 8.75;
float MUSCLE_TO_SENSOR_DIST = 70;
float MINIMUM_ANGLE = 5; //
float MAX_VEL_IN_DEG = 59;
float MIN_VEL_IN_DEG = 65.4;
float MEM_TRIGER_DEG = 24;

struct Control
{
     float theta;
     float vel;
};
//Control control;

namespace pid {
  class Pid;
}

class pid::Pid {
    /*! @class Pid
        eloat e_p;  // proportional error
    * creates pid object
    */
    public:
        // Constructor
        Pid(float k_p = 0.09, float k_i = 1., float k_d = 1.65,
            float k_p_vel = 1., float k_d_vel = 1.,
            unsigned char target_array = 24) {
            // good constant for straight lines
            // Kp = 0, Ki = 4, Kd = 0
            K_p = k_p;
            k_i = k_i;
            K_d = k_d;
            K_d_vel = k_d_vel;
            K_p_vel = k_p_vel;
            Ta = target_array;
            e_prev = 0.; // TODO: in the future this variables should be injected
            dt = 20; // sample time for changing controlled vars
            e_p = 0.;
            e_i = 0.;
            e_d = 0.;
            //e_prev = 0.;
            //last_time = 0;
            //last_control = 0.;
            //control_u = 0.;
            control_v = 90.;
            //control.theta = control_u;
            //control.vel = control_v;
        }
    public:
        float K_p; // proportional constant
        float K_i; // integral constant
        float K_d; // derivative constant
        float K_d_vel; // derivative constant for vel
        float K_p_vel; // derivative constant for vel
        unsigned char Ta; // target array (perfect position over trace)
        float e_prev; // previous error
        int dt;  // delta t
        float e_p;  // proportional error
        float e_i;  // integral error
        float e_d;  // derivative error
        int last_time;
        //float last_control;  // last control signal
        //float last_control_v;  // last control signal
        float control_u;  // initial control signal for angle
        float control_v;  // initial control signal for vel
        int active_sensors;
        float mean_dist;
        float OFFSET_DIST_WSIGN;
        Control control;
        int memory;

  Control correction_signal(unsigned char sensor_array) {
    // time counter
    unsigned long now = millis();
    unsigned long t_change = (last_time - now);

    if (t_change >= dt){
      //Serial.write(0x69);
      e_p = 0;
      mean_dist = 0;
      active_sensors = 0;
      for(int i = 0; i < 8; i++) {
          // we can ponderate the substraction below 
          //pid::Pid::e_p += pid::Pid::Ta[i] - sensor_array[i];
          active_sensors += 1*((sensor_array>>i)&1);
          if (i < 4){
            mean_dist += (((Ta>>i)&1) - ((sensor_array>>i)&1))*(4-i);
          }
          else{
            mean_dist += (((Ta>>i)&1) - ((sensor_array>>i)&1))*(3-i);
          }
        }

        if (mean_dist != 0) {
          mean_dist = mean_dist/active_sensors;
        }
        //else {
        //  e_p = e_prev;
        //}
        if (mean_dist == 0) {
          OFFSET_DIST_WSIGN = 0;
        }
        else if(signbit(mean_dist) == 1) {
          // negative offset if mean_dist is negative
          OFFSET_DIST_WSIGN = -1*OFFSET_DIST;
        }
        else {
          OFFSET_DIST_WSIGN = OFFSET_DIST;
        }
        e_p = atan((mean_dist*BETWEEN_SENSOR_DIST + OFFSET_DIST_WSIGN)/
                   MUSCLE_TO_SENSOR_DIST);
        e_p = e_p*180/PI;  // convert to angle
        // save previous error signal
        // some hardcoding :P
        // remember from where extreme we scape
        // enable hardcoding
        if(ENABLE_HC == 1){
          if(debug){
            Serial.print("Current e_p (in angle) = ");
            Serial.println(e_p);
            }
          // disable very soft correction
          if(sensor_array == SOFT_POS_SR){
              // 00011100
            e_p = SOFT_CORRECTION;
          }
          else if(sensor_array == SOFT_NEG_SR) {
            //  00111000
            e_p = -SOFT_CORRECTION;
          }
          // 00001100
          else if(sensor_array == MIN_POS_SR) {
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
        if(last_control >= MEM_TRIGER_DEG and
                                (abs(e_p) <= MIN_ERROR
                                or active_sensors == 0)) {
          control_u = EXTREME_CORRECTION;
          control_v = MIN_VEL_IN_DEG;
          memory = 1;
        }
        else if(last_control <= -MEM_TRIGER_DEG and
                                (abs(e_p) <= MIN_ERROR
                                or active_sensors == 0)){
          control_u = -EXTREME_CORRECTION;
          control_v = MIN_VEL_IN_DEG;
          memory = 1;
        }
        else {
          memory = 0;
        }
        if(debug){
          Serial.print("Current e_p (mm) = ");
          Serial.println(e_p);
          Serial.print("Active sensors (#) = ");
          Serial.println(active_sensors);
        }

      //float control_u = e_p;
      //if(debug){
      //  Serial.print("Current control_u (NO HC) = ");
      //  Serial.println(control_u);
      //}
      if(ENABLE_HC == 1){
        // when ENABLE_HC last_control = e_p
        if (memory != 1) {
          control_u = e_p;
          control_v = 64;
        }
        control.theta = control_u;
        control.vel = control_v;
        if(debug){
          Serial.print("Current control_u (HC) = ");
          Serial.println(control_u);
        }
      }
      else{
        if (memory != 1) {
          //e_i += (e_p * dt) * K_i ;  // e_i(0) = 0
          e_i += e_p * K_i ;  // e_i(0) = 0
          e_d = (e_p - e_prev); // dt
          control_u = K_p*e_p
          + e_i
          + K_d*e_d;
          control_v = (MIN_VEL_IN_DEG-MAX_VEL_IN_DEG)/EXTREME_CORRECTION *
                            (abs(e_p) * K_p_vel + abs(e_d) * K_d_vel)
                          + MAX_VEL_IN_DEG;
          control_v = fmax(MAX_VEL_IN_DEG, fmin(MIN_VEL_IN_DEG, control_v));
        }
        control.theta = control_u;
        control.vel = control_v;
      }

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
      last_time = now; // last time
      last_control = control_u;
      last_control_v = control_v;
      e_prev = e_p;
      if(straight == 1 and ENABLE_HC){
      return control;
      }
      else{
      return control;
      }
    }
    //else return last_control;
    else return control;
      last_control = last_control;
      last_control_v = last_control_v;
      e_prev = e_prev;
     // if(debug){
     //   Serial.println("inside dead update");
     //   Serial.print("e_prev");
     //   Serial.println(e_prev);
     //   Serial.print("Last control signal theta = ");
     //   Serial.println(last_control);
     //   Serial.print("Last control signal vel = ");
     //   Serial.println(last_control_v);
     // }

  }
};
