/**
 * @file ir_sensor.h
 * @author Felipe Guajardo (felipe.guajardo@solstic.io)
 * @brief Functions to interact with th IR sensors
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef IR_SENSORS_H_
#define IR_SENSORS_H_
namespace ir_sensor
{
    /**
     * @brief Initialize the necesary registers in order to use the ADCs given a threshold
     *
     * @param threshold vallue against the frontSensorRaw
     */
    void setup(unsigned int threshold = 100);  

    /**
     * @brief Value that the sensors are compared against in order to apss to binary
     * 
     */
    unsigned int threshold;

    /**
     * @brief time that it has to pass without detecting the other side to assume it as
     * a valid measurement
     * 
     */
    unsigned long side_time_threshold = 50;

    /**
     * @brief state of the side_sensor measurements.
     * 0: no mark is waiting confirmation
     * 1: left mark is waiting confirmation
     * 2: right mark is waiting confirmation
     * 
     */
    unsigned char side_sensor_state = 0;


    /**
     * @brief array used to store the front sensor measurments
     *
     */
    unsigned int frontSensorRaw[8];

    /**
     * @brief array used to store the side sensors readings
     *
     */
    unsigned int sideSensorsRaw[2];

    /**
     * @brief binary representation of the frontSensorRaw compared against the threshold
     *
     */
    unsigned char frontSensor;

    /**
     * @brief binary representation of the sideSensorRaw compared against the threshold
     *
     */
    unsigned char sideSensors;

    /**
     * @brief single front reading made from frontSensor array
     *
     */
    long front;

    /**
     * @brief Returns a byte having in each bit the corresponding to the
     * front sensor array state being the MSB the left side and the LSB the right side.
     *
     * @return unsigned char
     */
    unsigned char read_front(void);

    /**
     * @brief Funtion that returns 2 bits with the MSB the left sensor
     * state and the LSB the right sensor array.
     *
     * @return unsigned char
     */
    unsigned char read_sides(void);

    /**
     * @brief Use the side sensor information ir order to detect the start or end
     *
     * @return unsigned char 0 if no start or end is detected and 1 if start ot end is detected
     */
    unsigned char start_or_end_detected(void);

    unsigned char mark_detected(void);
#include <Arduino.h>

#define BLUE_PILL // which microcontroller is running the code

#ifdef BLUE_PILL
    const int FRONT_SENSORS[] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7};
    const int SIDE_SENSORS[] = {PB0, PB1};
    const int N_FRONT = 8;      // total number of fron sensors
    const int N_EACH_SIDES = 1; // total number on each side
#elif TEENSY35
#endif

    void setup(unsigned int threshold_value)
    {
        threshold = threshold_value;
        frontSensor = 0;
    }
    unsigned char read_front(void)
    {
        frontSensor = 0;
        for (int i = 0; i < N_FRONT; i++)
        {
            frontSensorRaw[i] = analogRead(FRONT_SENSORS[i]);
        }
        for (int i = 0; i < N_FRONT; i++)
        {
            if (frontSensorRaw[i] < threshold)
            {
                frontSensor |= _BV(i);
            }
        }
        return frontSensor;
    }
    unsigned char read_sides(void)
    {
        sideSensors = 0;
        for (int i = 0; i < N_EACH_SIDES; i++)
        {
            sideSensorsRaw[i] = analogRead(SIDE_SENSORS[i]);
        }
        for (int i = N_EACH_SIDES; i < 2 * N_EACH_SIDES; i++)
        {
            sideSensorsRaw[i] = analogRead(SIDE_SENSORS[i]);
        }
        for (int i = 0; i < N_EACH_SIDES; i++)
        {
            if (sideSensorsRaw[i] < threshold)
            {
                sideSensors |= _BV(i);
            }
        }
        for (int i = N_EACH_SIDES; i < 2 * N_EACH_SIDES; i++)
        {
            if (sideSensorsRaw[i] < threshold)
            {
                sideSensors |= _BV(i);
            }
        }
        return sideSensors;
    }

    unsigned char start_or_end_detected(void){
        return (sideSensors == 2);
    }

    unsigned char mark_detected(void){
        return(sideSensors == 1);
    }
    
    void test_routine(void)
    {
        Serial.print("threshold = ");
        Serial.println(threshold);
        read_front();
        for (int i = 0; i < 8; i++)
        {
            Serial.print(frontSensorRaw[i]);
            Serial.print(",");
        }
        Serial.println();
        for (int i = 0; i < 8; i++)
        {
            Serial.print((frontSensor >> i) & 1, BIN);
            Serial.print(",  ");
        }
        Serial.println();
        Serial.println("--------------------------------");
    }

    void test_sides(void)
    {
        unsigned long timer_test_sides = micros();
        unsigned char reading = read_sides();
        timer_test_sides = micros() - timer_test_sides;
        Serial.print("Raws left = ");
        Serial.print(sideSensorsRaw[0]);
        Serial.print(" right = ");
        Serial.println(sideSensorsRaw[1]);
        Serial.print("took = ");
        Serial.println(timer_test_sides);
        Serial.print("start_or_end_detected = ");
        Serial.print(start_or_end_detected());
        Serial.print(" mark_detected = ");
        Serial.println(mark_detected());
        Serial.println("------------------------");
        delay(100);
    }
};
#endif // IR_SENSORS_H_
