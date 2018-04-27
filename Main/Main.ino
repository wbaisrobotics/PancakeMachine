#include "Solenoid.hpp"
#include "PWMMotorController.hpp"
#include "Button.hpp"
#include "Servo.h"

// --- Ports ---
// Buttons
int startButtonPort = 40;

// Servos
int spatulaPort = 6;

// Solenoids
int dispenserPort = 36;
int extenderPort = 34;
int rotatorPort = 32;
int lifterPort = 30;

// Speed Controllers
int batterMixerPort = 5;

// --- Objects ---
// The button that triggers the pancake making process
Button startButton (startButtonPort); // change pin

// The piston that dispenses the batter onto the pan
Solenoid dispenser (dispenserPort);

// The piston that extends the arm into the pancake
Solenoid extender (extenderPort);

// The piston that rotates the arm for serving in the end
Solenoid rotator (rotatorPort);

// Lifts the arm
Solenoid lifter (lifterPort); // change pin

// Motor that mixes the batter throughout the run time
PWMMotorController batterMixer (batterMixerPort);

// The spatula that rotates to flip the pancake
Servo spatula;

void setup() {
  // DOES THE MIXER NEED A SPEED CONTROLLER?
  // Mix the batter throughout the process
  batterMixer.set(0.5);
  // Attach the servo representing the arm
  spatula.attach(spatulaPort);
}

void loop() {

  // Wait for start button to be pushed, checking every 100ms
  while (!startButton.isPushed()){
    delay (100);
  }

  // Assumes that system is currently in reset position
  // (In reset position arm is extended and rotated in, down, and flat)
  // End of loop returns to reset position, and default (all ports get LOW) is reset position

  // Adds batter onto the machine
  addBatter();
  

  // Wait for first side to be ready
  delay (10000);
  

  // Extend out to go under the pancake
  extendOut();
  // Lift the pancake up
  extendUp();
  
  // Flip the pancake
  spatulaDown();
  // Reset the spatula position
  spatulaUp();
  
  // Bring the arm back in
  extendIn();
  // Bring the arm back down
  extendDown();


  // Wait for other side to be ready
  delay(10000);


  // Extend out to go under the pancake
  extendOut();
  // Lift the pancake up
  extendUp();

  // Rotate the arm out above the plate
  rotateOut();
  
  // Drop the pancake onto the plate
  spatulaDown();
  // Reset the spatula position
  spatulaUp();

  
  // Go back to reset position
  extendIn();
  rotateIn();
  extendDown();
  
}

// Adds batter onto the plate
void addBatter (){
  dispenser.forward();
  delay(5000);
  dispenser.reverse();
}

// Rotates the arm out
void rotateOut(){
  if (rotator.isReverse()){
    rotator.forward();
    delay(3000);
  }
}

// Rotates the arm in
void rotateIn(){
  if (rotator.isForward()){
    rotator.reverse();
    delay(3000);
  }
}

// Extends the arm out
void extendOut(){
  if (extender.isReverse()){
    extender.forward();
    delay (1000);
  }
}

// Extends the arm in
void extendIn(){
  if (extender.isForward()){
    extender.reverse();
    delay (1000);
  }
}

// Extends the arm down
void extendDown(){
  if (lifter.isReverse()){
    lifter.forward();
    delay (1000);
  }
}

// Extends the arm up
void extendUp(){
  if (lifter.isForward()){
    lifter.reverse();
    delay (1000);
  }
}

// Rotates the spatula so that it is right side up
void spatulaUp(){
  if (spatula.read() != 0){
    spatula.write(0);
    delay (2000);
  }
}

// Rotates the spatula so that it is right side down
void spatulaDown (){
  if (spatula.read() != 180){
    spatula.write(180);
    delay (2000);
  }
}

