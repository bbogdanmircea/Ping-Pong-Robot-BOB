    /*     Simple Stepper Motor Control Exaple Code
     *      
     *  by Dejan Nedelkovski, www.HowToMechatronics.com
     *  
     */
     
    // Defines pins numbers
    const int stepPin = 14; //A0
    const int dirPin = 15; //A1 
    int customDelay,customDelayMapped; // Defines variables
     
    void setup() {
      // Sets the two pins as Outputs
      pinMode(stepPin,OUTPUT);
      pinMode(dirPin,OUTPUT);
     
      digitalWrite(dirPin,HIGH); //Enables the motor to move in a particular direction
    }
    void loop() {
      customDelayMapped = 1;
      // Makes pules with custom delay, depending on the Potentiometer, from which the speed of the motor depends
      digitalWrite(stepPin, HIGH);
      delay(customDelayMapped);
      digitalWrite(stepPin, LOW);
      delay(customDelayMapped);
    }
   
    
