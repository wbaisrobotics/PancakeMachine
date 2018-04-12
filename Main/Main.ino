#include "Solenoid.hpp"

Solenoid dispenser (36);

Solenoid extender (34);

Solenoid rotator (32);

void setup() {
}

// Move the solenoid to forward position, wait 5 seconds, move the solenoid to reverse position, wait 5 seconds
void loop() {

  rotateOut();
  addBatter();
  delay (10000);
  rotateIn();
  extendOut();
  delay(2000);
  extendIn();
  rotateOut();
  
//
//dispenser.forward();
//rotator.forward();
//extender.forward();

  //delay(10000);
  
}

// Adds batter onto the plate
// Should be called after rotateOut()
void addBatter (){
  dispenser.forward();
  delay(5000);
  dispenser.reverse();
}

// Rotates the arm out
void rotateOut(){
  if (rotator.isReverse()){
    rotator.forward();
    delay(1000);
  }
}

// Rotates the arm in
void rotateIn(){
  if (rotator.isForward()){
    rotator.reverse();
    delay(1000);
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

