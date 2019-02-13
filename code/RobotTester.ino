#include <Servo.h> 
#define INLENGTH 16 //Maximum input string will be 16 characters.. probably more than we need :-)
#define INTERMINATOR 13 //Decimal representation of ascii character

//Arduino pin assignments
#define PIN_TOP 9
#define PIN_BOT 8
#define PIN_FEED 7
#define PIN_H_SWEEP 6
#define PIN_V_SWEEP 5
#define PIN_ROT 4
#define PIN_AGITATOR 3
#define PIN_IR 2
#define PIN_REVERSE_BOT 42
#define PIN_REVERSE_TOP 40

#define DEF_TOP 0
#define DEF_BOT 0
#define DEF_FEED 140
#define DEF_H_SWEEP 90
#define DEF_V_SWEEP 90
#define DEF_ROT 90
#define DEF_AGITATOR 103

#define MOTOR_PULSE_ZERO 1000
#define MOTOR_PULSE_180 1940
#define SERVO_PULSE_ZERO 544
#define SERVO_PULSE_180 2300

char inString[INLENGTH+1];
int inCount;
int continuous = 0; //Needs to be int, storing this as # of milliseconds

byte topMot=0;
byte botMot=0;
byte hPos=0;
byte vPos=0;
byte rPos=0;

Servo motorBottom;
Servo motorTop;
Servo servoFeed;
Servo servoHSweep;
Servo servoVSweep;
Servo servoRotation;
Servo servoAgitator;

boolean topRev = false;
boolean botRev = false;

void setServoPositions(int _motorBottom, int _motorTop, int _servoHSweep, int _servoVSweep, int _servoRotation){
  motorBottom.writeMicroseconds( map(_motorBottom,0,180, MOTOR_PULSE_ZERO, MOTOR_PULSE_180) );
  motorTop.writeMicroseconds( map(_motorTop,0,180, MOTOR_PULSE_ZERO, MOTOR_PULSE_180) );
  servoHSweep.writeMicroseconds( map(_servoHSweep,0,180, SERVO_PULSE_ZERO, SERVO_PULSE_180) );
  servoVSweep.writeMicroseconds( map(_servoVSweep,0,180, SERVO_PULSE_ZERO, SERVO_PULSE_180) );
  servoRotation.writeMicroseconds( map(_servoRotation,0,180, SERVO_PULSE_ZERO, SERVO_PULSE_180) );
}

void defaultServoPositions(){
  setServoPositions(DEF_BOT, DEF_TOP, DEF_H_SWEEP, DEF_V_SWEEP, DEF_ROT);
  servoFeed.writeMicroseconds( map(DEF_FEED,0,180, SERVO_PULSE_ZERO, SERVO_PULSE_180) );
}

void setup() 
{ 
  Serial.begin(9600);
  motorBottom.attach(PIN_BOT);
  motorTop.attach(PIN_TOP);
  servoFeed.attach(PIN_FEED);
  servoHSweep.attach(PIN_H_SWEEP);
  servoVSweep.attach(PIN_V_SWEEP);
  servoRotation.attach(PIN_ROT);
  servoAgitator.attach(PIN_AGITATOR, SERVO_PULSE_ZERO, SERVO_PULSE_180);
  defaultServoPositions();
  pinMode(PIN_REVERSE_BOT, OUTPUT);
  pinMode(PIN_REVERSE_TOP, OUTPUT);
  servoAgitator.writeMicroseconds( map(DEF_AGITATOR,0,180, SERVO_PULSE_ZERO, SERVO_PULSE_180) );
  
  Serial.println("Enter a letter with an optional number (0-180) to control the robot (ex: t30)");
  Serial.println("t# - Set top motor speed");
  Serial.println("b# - Set bottom motor speed");
  Serial.println("q - Reverse top motor");
  Serial.println("s - Reverse bottom motor");
  Serial.println("h# - Set horizontal servo");
  Serial.println("v# - Set vertical servo");
  Serial.println("r# - Set rotation servo");
  Serial.println("f - Feed the ball");
  Serial.println("c# - Continuous feed every #ms");
}

void loop()
{
  inCount = 0;
  if(continuous == 0){//Not in continuous feed mode
    do {
      while (!Serial.available());             // wait for input
      inString[inCount] = Serial.read();       // get it
      if (inString [inCount] == INTERMINATOR) break;
    } 
    while (++inCount < INLENGTH);
  }
  else{//In continuous feed mode
    delay(continuous);
    do {
      if(!Serial.available()) break;           //If there's nothing to read just continue to feed
      inString[inCount] = Serial.read();       // get it
      continuous = 0;    //we've got something; stop continuous feed
      if (inString [inCount] == INTERMINATOR) break;
    } 
    while (++inCount < INLENGTH);
  }

  if(continuous == 0){//Not in continuous feed mode
    inString[inCount] = 0;  
    char wheel = inString[0];
    char inputParameter[INLENGTH];
    for(int i = 1; i < INLENGTH; i++){
      inputParameter[i-1] = inString[i];
    }
    Serial.println(inputParameter);
    //This section used to be a single if statement and then I kept adding slowly over time, but 
    //haven't been bothered to make it into a switch :-)
    
    if(wheel == 'p'){//Print current speed/location parameters for calibration, configuration, etc
      char output[20];
      sprintf(output,"%d/%d/%d/%d/%d/%d/%d",topMot,botMot,vPos,hPos,rPos,!topRev,!botRev);
      Serial.println(output);
    }
    if(wheel == 'c'){//
      continuous=atoi(inputParameter);
    }
    if(wheel == 'a'){//Set the agitator servo speed
      Serial.println("Agitator");  
      servoAgitator.write(atoi(inputParameter) );
    }
    if(wheel == 't'){//Set the top motor speed
      Serial.println("Top");  
      topMot = atoi(inputParameter);
      motorTop.writeMicroseconds( map(topMot,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
    }
    if(wheel == 'b'){//Set the bottom motor speed
      Serial.println("Bottom");
      botMot = atoi(inputParameter);
      motorBottom.writeMicroseconds( map(botMot,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
    }
    if(wheel == 'q'){//Reverse the top motor
      Serial.println("Reverse top");
      motorTop.writeMicroseconds( map(0,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
      topRev=!topRev;
      digitalWrite(PIN_REVERSE_TOP, topRev);
    }
    if(wheel == 's'){//Reverse the bottom motor
      Serial.println("Reverse bot");
      motorBottom.writeMicroseconds( map(0,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
      botRev=!botRev;
      digitalWrite(PIN_REVERSE_BOT, botRev);
    }
    if(wheel == 'd'){//Set both motor speeds
      Serial.println("Both");
      topMot=atoi(inputParameter);
      botMot=atoi(inputParameter);
      motorTop.writeMicroseconds( map(topMot,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
      motorBottom.writeMicroseconds( map(botMot,0,180,MOTOR_PULSE_ZERO,MOTOR_PULSE_180) );
    }
    if(wheel == 'f'){//Feed the ball
      Serial.println("Feed");
      feed();
    }
    if(wheel == 'r'){//Set the rotation servo position
      Serial.println("Rotation");
      rPos=atoi(inputParameter);
      servoRotation.writeMicroseconds( map(rPos,0,180,SERVO_PULSE_ZERO,SERVO_PULSE_180) );
    }
    if(wheel == 'v'){//Set the vertical servo position
      Serial.println("Vertical");
      vPos = atoi(inputParameter);
      servoVSweep.writeMicroseconds( map(vPos,0,180,SERVO_PULSE_ZERO,SERVO_PULSE_180) );
    }
    if(wheel == 'h'){//Set the horizontal servo position
      Serial.println("Horizontal");
      hPos = atoi(inputParameter);
      servoHSweep.writeMicroseconds( map(hPos,0,180,SERVO_PULSE_ZERO,SERVO_PULSE_180) );
    }
  }//End not in continuous
  else{//We're in continuous mode, so feed the ball
    feed();
  }
}

void feed(){
  servoFeed.writeMicroseconds( map(5,0,180,SERVO_PULSE_ZERO,SERVO_PULSE_180) );
  delay(600);//Wait for the servo to finish pushing the ball up before we retract
  servoFeed.writeMicroseconds( map(140,0,180,SERVO_PULSE_ZERO,SERVO_PULSE_180) );
}

