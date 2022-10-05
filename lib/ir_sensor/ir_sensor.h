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
     * @brief Initialize the necesary registers in order to use the ADCs
     * 
     */
    void setup(void);

    /**
     * @brief array used to store the front sensor measurments  
     * 
     */
    unsigned int frontSensor[8];
    
    /**
     * @brief array used to store the side sensors readings
     * 
     */
    unsigned int sideSensors[2];

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
}