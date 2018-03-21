#include "Solenoid.hpp"

// Initialize the dispenser on pin 13
Solenoid dispenserStopper (13);

// Initialize the arm extendor on pin 12
Solenoid armExtendor (12);

// Initialize the pancake flipper on pin 11
Solenoid pancakeFlipper (11);


// Initialize the mixing motor on pin 10
PWMMotorController mixingMotor (10);

// Initialize the other motor on pin 9
PWMMotorController otherMotor (9);


void setup() {
}

// Move the solenoid to forward position, wait 5 seconds, move the solenoid to reverse position, wait 5 seconds
void loop() {
  
 
  
}
