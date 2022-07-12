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
    int n_lap = 0;  // lap number
    gnium::Gnium gnium = gnium::Gnium(mode, type, n_lap);
    // TODO (wis) gnium.setup()

    while(1) {
        // run repetedly here
        Serial.print("Gniiiium!i \n");
        if (gnium.Mode == 1) {  // compite
             gnium.run_lap(gnium.Lap_n);
             ++gnium.Lap_n; 
         }
        
        else if (gnium.Mode == 0) {  // test
             gnium.test(); // test types?? (as argument)
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
