/**
 * @brief this file has the functions tu run periodically the functions that are necessary 
 * read the state of a sensor, calculate the output of a controller and toggle two pins
 * to controla a servo and a motor.
 * 
 */

#define PERIOD 20000 //in usecs
#define SERVO_PIN PB15
#define MOTOR_PIN PB14
#include <Arduino.h>


namespace events{
    /**
     * @brief method that calls the necessary functions at the appropiate time.
     * It should be called as often as posible
     * 
     */
    void run();

    /**
     * @brief period that the servo signal keeps turned on in usecs
     * 
     */
    unsigned long servo_period;
    
    /**
     * @brief period that the motor signal keeps turned on in usecs
     * 
     */
    unsigned long motor_period;

    /**
     * @brief timer used to store the time since the last rising edge
     * 
     */
    unsigned long global_timer;

    void init(void){
        pinMode(SERVO_PIN,OUTPUT);
        pinMode(MOTOR_PIN,OUTPUT);
        global_timer = micros();
    }

    /**
     * @brief state byte
     * B0 is used to signal the correct change in the motor PWM
     * B1 is used to signal the correct change in the servo PWM
     * B4 is used to signal the midle  routine
     * B3 is used to signal the sensor reading routine
     * B4 is used to signal the controller routine
     */
    byte duty_state = 0;

    const byte MOTOR_BIT = 1;
    const byte SERVO_BIT = B10;
    const byte MIDDLE_BIT = _BV(2);
    const byte SENSOR_BIT = _BV(3);
    const byte CONTROLLER_BIT = _BV(4);
    
    unsigned long this_time;

    void midle_routine();
    void sensor_routine();
    void controller_routine();
    
    void run(){
        this_time = micros();
        if ((this_time - global_timer) > PERIOD){
            //a new period starts, generate rising edge;
            global_timer = micros();
            digitalWrite(MOTOR_PIN,HIGH);
            digitalWrite(SERVO_PIN,HIGH);
            duty_state = B11;
            //duration of the pulse is sensitive so this part stalls the code
            while (duty_state){
                this_time = micros();
                if ((this_time-global_timer)> motor_period){
                    digitalWrite(MOTOR_PIN,LOW);
                    duty_state &= ~MOTOR_BIT;
                }
                if ((this_time-global_timer)> servo_period){
                    digitalWrite(MOTOR_PIN,LOW);
                    duty_state &= ~SERVO_BIT;
                }
            }
            // signal that the 
            duty_state |= MIDDLE_BIT | SENSOR_BIT | CONTROLLER_BIT;
            midle_routine();
            duty_state &= ~MIDDLE_BIT;
            sensor_routine();
            duty_state &= ~SENSOR_BIT;
            controller_routine();
            duty_state &= ~CONTROLLER_BIT;
            //wait for next rising edge
        }
    }
}

