
#include "ESC.h"
#include <Servo.h>

#define LED_PIN (13)                                      // Pin for the LED 
#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (1250)                                  // Set the Minimum Speed in microseconds

// Defines pins numbers
const int stepPin = 14; //A0
const int dirPin = 15; //A1 
int customDelay,customDelayMapped; // Defines variables

ESC myESCTOP (9, SPEED_MIN, SPEED_MAX, 500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESCBOT (10, SPEED_MIN, SPEED_MAX, 500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  //ESC Init
  myESCTOP.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  myESCBOT.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  //stepper init
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH); //Enables the motor to move in a particular direction

  myservo.attach(6);  // attaches the servo on pin 6 to the servo object
}

void loop() {
  int i;
  bool LR = 0;
  oESC = 1250;

  myESCTOP.speed(oESC);                                    // tell ESC to go to the oESC speed value
  myESCBOT.speed(oESC);
  

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
}
