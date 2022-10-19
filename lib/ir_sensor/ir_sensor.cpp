#include "ir_sensor.h"
#include <Arduino.h>

#define BLUE_PILL //which microcontroller is running the code

#ifdef BLUE_PILL
const int FRONT_SENSORS[] = {PA0,PA1,PA2,PA3,PA3,PA4,PA5,PA6,PA7};
const int SIDE_SENSORS[] = {PB0,PB1};
const int N_FRONT = 8; //total number of fron sensors
const int N_EACH_SIDES =1; //total number on each side
#elif TEENSY35 
#endif

namespace ir_sensor{
    void setup(unsigned int threshold){
        ir_sensor::threshold = threshold;
        frontSensor=0;
    }
    unsigned char read_front(void){
        frontSensor=0;
        for (int i = 0; i < N_FRONT; i++){
            frontSensorRaw[i] = analogRead(FRONT_SENSORS[i]); 
        }
        for (int i = 0; i < N_FRONT; i++){
            if (frontSensorRaw[i] > threshold) {
                frontSensor |= _BV(i);
            }
        }
        return frontSensor;
    }
    unsigned char read_sides(void){
        sideSensors = 0;
        for (int i = 0; i < N_EACH_SIDES; i++){
            sideSensorsRaw[i] = analogRead(SIDE_SENSORS[i]);
        }
        for (int i = N_EACH_SIDES; i < 2*N_EACH_SIDES; i++){
            sideSensorsRaw[i] = analogRead(SIDE_SENSORS[i]);
        }
        for (int i = 0; i < N_EACH_SIDES; i++){
            if (sideSensorsRaw[i] > threshold){
                sideSensors |= _BV(i);
            }
        }
        for (int i = N_EACH_SIDES; i < 2*N_EACH_SIDES; i++){
            if (sideSensorsRaw[i] > threshold){
                sideSensors |= _BV(i);
            }
        }
        return sideSensors;
    }
}