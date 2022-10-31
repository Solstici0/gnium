/*! @file main.cpp is the main code file that calls all other modules
 *  for testing and running 3 laps and learn to improve performance 
 *  inbetween iterations
*/

#include <Arduino.h>
#include <gnium.h>
#include <ir_sensor.h>
#include <events.h>
//gnium::mode mode = gnium::race;  // 0 for test, 1 for compite
gnium::mode mode = gnium::test_events;  // 0 for test, 1 for compite

// This options needs less memory. Why?

void events::midle_routine(){
    delay(5);
    Serial.println("midle");
}
void events::sensor_routine(){
    unsigned long t_init = micros();
    ir_sensor::read_front();
    unsigned long t_end =micros();
    Serial.print("read_front took ");
    Serial.print(t_end-t_init);
    Serial.println(" us");
}
void events::controller_routine(){
    delay(5);
    //whis routine should set the new values of motor_period and servo_period in us
    events::motor_period +=2;
    events::servo_period -=1;
    if (events::motor_period >= 180){
        events::motor_period = 10;

    }
    if (events::servo_period < 10){
        events::servo_period = 180;
    }
    Serial.println("control_routine");
}
int main() {
    // setup code here
    init();
    Serial.begin(115200); // open the serial port at 115200 bps:
    int type = 0;  // 0 for 5-wheels, 1 for classic
    int n_lap = 0;  // lap number
    unsigned int threshold = 100;
    events::init();


    // gnium::Gnium gnium = gnium::Gnium(mode=mode,
    //                                   type=type,
    //                                   n_lap=n_lap,
    //                                   threshold=threshold);
    // TODO (wis) gnium.setup()

    while(1) {
        // run repetedly here
        // Serial.print("Gniiiium!i \n");
        if (mode == gnium::race) {  // compite
            // gnium.run_lap(gnium.Lap_n);
            // ++gnium.Lap_n;

            // // third lap finished
            // if (gnium.Lap_n == 2) {
            //     break;
            // }
        }
        else if (mode == gnium::test_follow_trace ) {  // test follow_trace
            // gnium.follow_trace(gnium.Train_pwm,
            //                     gnium.Pid);
       }
        else if (mode == gnium::test_ir_sensors ) {  // test ir_sensors reading
            ir_sensor::test_routine();
        }
        else if (mode == gnium::test_servo ) {  // test servo (demo)
            servo::test_routine();
        }
        else if (mode == gnium::test_servo_offset ) {  // test servo offset
            servo::test_offset();
        }
        else if (mode == gnium::test_muscle ) {  // test muscle
            muscle::test_routine();
        }
        else if (mode == gnium::test_vel ) {  // test muscle
            float testing_vel = 75;  // velocity in dregree
            muscle::test_vel(testing_vel);
        }
        else if (mode == gnium::test_forward_vel ) {  // test muscle
            float steady_vel = 75;  // velocity in dregree
            muscle::test_forward_vel(steady_vel);
        }
        else if (mode == gnium::test_events){
            events::run();

        }
    }
}
// */

// and this one needs more
/*
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.print("Gniiiium!i \n");
}
*/
