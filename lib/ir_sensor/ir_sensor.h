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
     * @brief Function that refreshes the frontSensors array
     * 
     */
    void readFront(void);

    /**
     * @brief Funtion that refreshes the sideSensors array
     * 
     */
    void readSides(void);

    /**
     * @brief Use the side sensor information ir order to detect the start or end
     * 
     * @return int 0 if no start or end is detected and 1 if start ot end is detected 
     */
    int start_or_end_detected(void);
};