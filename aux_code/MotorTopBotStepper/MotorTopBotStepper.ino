// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// Defines pins numbers
const int stepPin = 14; //A0
const int dirPin = 15; //A1 
int customDelay,customDelayMapped; // Defines variables

AF_DCMotor motorTop(4);
AF_DCMotor motorBot(3);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorTop.setSpeed(100);
  motorBot.setSpeed(100);
  motorTop.run(RELEASE);
  motorBot.run(RELEASE);
  //stepper init
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH); //Enables the motor to move in a particular direction
}

void loop() {
  uint8_t i;
  
customDelayMapped = 3;
digitalWrite(stepPin, HIGH);
delay(customDelayMapped);
digitalWrite(stepPin, LOW);
delay(customDelayMapped);
  
motorTop.run(BACKWARD);
motorBot.run(BACKWARD);
motorTop.setSpeed(100);
motorBot.setSpeed(100);  
}
