#include <Arduino.h>
#include <pid.h>

// This options needs less memory. Why?
// /*
int main() {
    // setup code here
    Serial.begin(115200); // open the serial port at 115200 bps:

    while(1) {
        // run repetedly here
        Serial.print("Gniiiium!i \n");
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
