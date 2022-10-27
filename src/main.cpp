/*! @file main.cpp is the main code file that calls all other modules
 *  for testing and running 3 laps and learn to improve performance 
 *  inbetween iterations
*/

#include <Arduino.h>
// #include <pwm.h> // TODO refactor. Should be inside gnium?
#include <gnium.h>
#include <ir_sensor.h>
//#include <servo.h>

gnium::mode mode = gnium::test_servo;  // 0 for test, 1 for compite

// This options needs less memory. Why?
// /*
int main() {
    // setup code here
    init();
    Serial.begin(115200); // open the serial port at 115200 bps:
    int type = 0;  // 0 for 5-wheels, 1 for classic
    int n_lap = 0;  // lap number
    gnium::Gnium gnium = gnium::Gnium(mode, type, n_lap);
    // TODO (wis) gnium.setup()

    while(1) {
        // run repetedly here
        Serial.print("Gniiiium!i \n");
        if (mode == gnium::gnium) {  // compite
            gnium.run_lap(gnium.Lap_n);
            ++gnium.Lap_n;

            // third lap finished
            if (gnium.Lap_n == 2) {
                break;
            }
        }
        
        else if (mode == gnium::test_ir_sensors ) {  // test
            ir_sensor::test_routine();
        }
        else if (mode == gnium::test_servo ) {  // test
            servo::test_routine();
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
