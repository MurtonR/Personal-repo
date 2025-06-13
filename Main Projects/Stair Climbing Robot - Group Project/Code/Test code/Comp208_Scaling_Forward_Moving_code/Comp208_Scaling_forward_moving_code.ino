#include <Encoder.h>
//variables for motor1
int encoderA = 0;
int encoderB = 0;
int motorA = 5;
int motorB = 6;
int motorE = 0;
//variables for motor2
int encoder2A = 0;
int encoder2B = 0;
int motor2A = 10;
int motor2B = 11;
int motor2E = 0;
//variable for back motors
int motorNA = 3;
int motorNB = 2;
int motorNE = 0;
int motor2NA = 13;
int motor2NB = 12;
int motor2NE = 0;

//sets up encoder for both wheels
Encoder wheelSet1(encoderA, encoderB);
Encoder wheelSet2(encoder2A, encoder2B);

void motorDriving(int speed, int motorA, int motorB, int motorE){
 //ensure speed is within bounds
  if (speed < -255){
    speed = -255;
  }
  if (speed > 255){
    speed = 255;
  }
  
  //sets motors to spin forward, backwards or not at all
  if(speed > 0){
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
  }
   if(speed < 0){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
  }
   if(speed == 0){
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, LOW);
  }
  
}


void setup() {
  //set the pin modes of the motor pins and encoder pins
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(motorE, OUTPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(encoder2A, INPUT);
  pinMode(encoder2B, INPUT);
  pinMode(motorNA, OUTPUT);
  pinMode(motorNB, OUTPUT);
  pinMode(motor2NA, OUTPUT);
  pinMode(motor2NB, OUTPUT);
  Serial.begin(9600);
  
}

void loop(){
  //moves forwards for a second and then backwards for a second
  motorDriving(-255, motorA, motorB, motorE);
  motorDriving(100, motor2A, motor2B, motor2E);
  digitalWrite( motorNA, HIGH);
  digitalWrite( motorNB, LOW);
  digitalWrite( motor2NA, HIGH);
  digitalWrite( motor2NB, LOW);
  

}
