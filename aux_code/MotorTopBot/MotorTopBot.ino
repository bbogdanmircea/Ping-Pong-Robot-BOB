// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

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
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");
  
motorTop.run(BACKWARD);
motorBot.run(BACKWARD);
motorTop.setSpeed(35);
motorBot.setSpeed(35);  
//  motor.run(FORWARD);
//  for (i=0; i<100; i++) {
//    motor.setSpeed(i);  
//    delay(10);
// }
// 
//  for (i=100; i!=0; i--) {
//    motor.setSpeed(i);  
//    delay(10);
// }
//  
//  Serial.print("tock");
//
//  motor.run(BACKWARD);
//  for (i=0; i<100; i++) {
//    motor.setSpeed(i);  
//    delay(10);
// }
// 
//  for (i=100; i!=0; i--) {
//    motor.setSpeed(i);  
//    delay(10);
// }
//  
//
//  Serial.print("tech");
//  motor.run(RELEASE);
//  delay(1000);
}
