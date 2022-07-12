/*! @file main.cpp is the main code file that calls all other modules
 *  for testing and running 3 laps and learn to improve performance 
 *  inbetween iterations
*/

#include <Arduino.h>
#include <pid.h> // TODO refactor. Should be inside gnium?
#include <pwm.h> // TODO refactor. Should be inside gnium?
#include <gnium.h>

// This options needs less memory. Why?
// /*
int main() {
    // setup code here
    Serial.begin(115200); // open the serial port at 115200 bps:
    int mode = 0;  // 0 for test, 1 for compite
    int type = 0;  // 0 for 5-wheels, 1 for classic
    gnium::Gnium gnium = gnium::Gnium(mode, type);
    // TODO (wis) gnium.setup()

    while(1) {
        // run repetedly here
        Serial.print("Gniiiium!i \n");
        // TODO (wis)
        // if (gnium.mode == 'compite') {
        //     gnium.run_lap(gnium::lap_n)
        //     gnium::lap_n += 1
        // }
        //
        // else if (gnium.mode == 'test') {
        //     gnium.test() // test types?? (as argument)
        // }

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
