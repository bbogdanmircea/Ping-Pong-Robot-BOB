// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>

// Defines pins numbers
const int stepPin = 14; //A0
const int dirPin = 15; //A1 
int customDelay,customDelayMapped; // Defines variables

AF_DCMotor motorTop(4);
AF_DCMotor motorBot(3);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

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

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  int i;
  bool LR = 0;

  for (pos = 0; pos <= 110; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    customDelayMapped = 2; //delay between steps, higher the value slower the speed of the stepper
digitalWrite(stepPin, HIGH);
delay(customDelayMapped);
digitalWrite(stepPin, LOW); 
delay(customDelayMapped);

  }

   for (pos = 110; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    customDelayMapped = 2; //delay between steps, higher the value slower the speed of the stepper
digitalWrite(stepPin, HIGH);
delay(customDelayMapped);
digitalWrite(stepPin, LOW); 
delay(customDelayMapped);

  }

//set the speed and direction of Top and Bot Motors
motorTop.run(BACKWARD);
motorBot.run(BACKWARD);
motorTop.setSpeed(100);
motorBot.setSpeed(100);




 
}
