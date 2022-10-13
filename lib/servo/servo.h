/**
 * @file servo.h
 * @brief Function to interact with servo motor
 * @version 0.1
 * @date 2022-10-12
 */

namespace servo{
  /**
   * @brief
   * @param
   */
   void setup();
   /**
    * @brief initializa pins for servo motor
    * @params pin numbers
    */

   void set_velocity(float angle_correction);
   /**
    * @brief set new angle given information from pid
    * @param angle_correction given by pid
    */

};
