#include "Solenoid.hpp"
#include "PWMMotorController.hpp"
#include "Button.hpp"
#include "Servo.h"

// --- Ports ---
// Buttons
int startButtonPort = 40;
int rotateInSwitchPort = 46;

// Servos
int spatulaPort = 26;

// Solenoids
int dispenserPort = 32;
int extenderPort = 34;
int lifterPort = 36;

// Speed Controllers
int batterMixerPort = 5;
int rotatorPort = 6;

// --- Objects ---
// The button that triggers the pancake making process
Button startButton (startButtonPort);

// The limit switch which hits when rotated in
Button inRotationSwitch (rotateInSwitchPort);

// The piston that dispenses the batter onto the pan
Solenoid dispenser (dispenserPort);

// The piston that extends the arm into the pancake
Solenoid extender (extenderPort);

// Lifts the arm
Solenoid lifter (lifterPort);

// Motor that mixes the batter throughout the run time
PWMMotorController batterMixer (batterMixerPort);

// Controls the rotation of the arm
PWMMotorController rotationMotor (rotatorPort);

// The spatula that rotates to flip the pancake
Servo spatula;

void setup() {
  // Mix the batter throughout the process
  batterMixer.set(0.2);
  // Make sure the motor is off
  rotationMotor.set(0);
  // Attach the servo representing the arm
  spatula.attach(spatulaPort);
  spatula.write(0);
  Serial.begin(9600);
}

void loop() {

  // Wait for start button to be pushed, checking every 100ms
  while (!startButton.isPushed()){
    delay (100);
  }

  addBatter();

  delay (3000);

  extender.forward();
  delay (2000);

  lifter.forward();
  delay (4000);

  rotateIn();

  extender.reverse();
  spatula.write(180);

  delay (2000);
  spatula.write(0);
  
  rotateIn();

  lifter.reverse();
  delay (3000);

  delay (3000);

  extender.forward();
  delay (2000);

  lifter.forward();
  delay (3000);

  rotateOut();
  
  spatula.write(180);
  delay (2000);
  spatula.write(0);

  rotateIn();

  extender.reverse();
  delay (2000);

  rotateIn();

  lifter.reverse();
  delay (3000);

  rotateIn();
  
  
}

// Adds batter onto the plate
void addBatter (){
  dispenser.forward();
  delay(5000);
  dispenser.reverse();
}

void rotateIn(){
  bool switchReached = (!inRotationSwitch.isPushed()); // Wired opposite
  Serial.println(switchReached);
  while (!switchReached){
    rotationMotor.set(0.2);
    switchReached = (!inRotationSwitch.isPushed()); // Wired opposite
    Serial.println(switchReached);
    delay (50);
  }
  rotationMotor.set(0);
}

void rotateOut(){
  rotationMotor.set(-0.2);
  delay (2300);
  rotationMotor.set(0);
}

