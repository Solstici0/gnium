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

namespace ir_sensor{
    /**
     * @brief Initialize the necesary registers in order to use the ADCs given a threshold
     * 
     * @param threshold vallue against the frontSensorRaw
     */
    void setup(unsigned int threshold);

    /**
     * @brief Value that the sensors are compared against in order to apss to binary
     * 
     */
    unsigned int threshold;

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

    /**
     * @brief routine that prints to serial the reading of the sensors
     * 
     */
    void test_routine(void);
};