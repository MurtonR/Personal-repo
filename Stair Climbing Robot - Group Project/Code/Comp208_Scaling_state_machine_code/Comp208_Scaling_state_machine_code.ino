#include <Encoder.h>  // not used at the moment
// attach to correct pin outs when Ultrasonic sensor is added onto frame
#define echoPin 8
#define trigPin 9

enum RobotState_enum { FORWARD,
                       TURNING };  //State of the Robot
enum SensorStates_enum { STAIR,
                         GROUND };  //State of the Sensors
static RobotState_enum states; //Instance of the robot state
static SensorStates_enum sensors; //Instance of the sensor state

//pins for wheel left
int motorBRA = 3;
int motorBRB = 2;
//int motorWLE = 0;

//pins for motor wheel right
int motorBLA = 13;
int motorBLB = 12;
//int motorWRE = 0;

//pins for hook wheel right (PWM pins)
int motorFRA = 5;
int motorFRB = 6;

//pins for hook wheel left (PWM pins)
int motorFLA = 10; 
int motorFLB = 11;

//pin for ultrasonic sensor
int ultrasonicFront;

//variable for threshold distance of ultrasonic sensor readings 
int setDist;
int usDuration;
int usSpeed;
int usDistance;

// tilt counter variables
int tiltCounter;
int firstTilt;
int secondTilt;
unsigned long second = 1000;
unsigned long timer = 0;
int tiltPin = 4;

//Misc variables for alternate code
bool ground = false;

void motorDriving(int speed, int motorA, int motorB) {  //function for motor driving
  
  //Make sure speed is within the bounds                           
  if (speed < -255) { 
    speed = -255;
  }
  if (speed > 255) {
    speed = 255;
  }

  //sets motors to spin forward, backwards or not at all depending on the sppeed
  if (speed > 0) {
    analogWrite(motorA, speed);
    analogWrite(motorB, -speed);
  }
  if (speed < 0) {
    analogWrite(motorA, -speed);
    analogWrite(motorB, speed);
  }
  if (speed == 0) {
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
  }
  
}


void setup() {
  //set the pin modes of the motor pins and encoder pins
  pinMode(tiltPin, INPUT);
  pinMode(motorBRA, OUTPUT);
  pinMode(motorBRB, OUTPUT);
  //pinMode(motorE, OUTPUT);
  pinMode(motorBLA, OUTPUT);
  pinMode(motorBLB, OUTPUT);
  //pinMode(motorWRE, OUTPUT);
  pinMode(motorFRA,OUTPUT);
  pinMode(motorFRB,OUTPUT);
  pinMode(motorFLA,OUTPUT);
  pinMode(motorFLB,OUTPUT);
  firstTilt = digitalRead(tiltPin);
  Serial.begin(9600);
}

void loop(){


 secondTilt = digitalRead(tiltPin);  //if the tilt sensor is not tilted and it isnt the first time this has happened, the robot needs to turn
  if (secondTilt == firstTilt && tiltCounter == 1){
    sensors = GROUND;
  }
  if(secondTilt != firstTilt){ //ensures that turning does not occur immediately
     tiltCounter ++;
  }
  else{ //base state is stair climbing
    sensors = STAIR;
  }

  if (tiltCounter = 0) {
    // loop
    // go forward, turn right if something is close
    // until no wall, go forward
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    usDuration = pulseIn(echoPin, HIGH);  //time
    usSpeed = 0.034;
    usDistance = usSpeed * usDuration / 2;  //distance = speed x time / 2
    Serial.println(usDistance);
  }
   stairStates(sensors);
}



void stairStates(uint8_t sensors) {  
  switch (states) {
    /*if the robot is tilted run the turning code, else run the moving upward code*/
    case FORWARD:
    if(sensors == GROUND){
    motorStop(); //should prevent gears stalling or catching
    states = TURNING;
    }
    else{
      movingUpward();
    }
    break;

    case TURNING:
    if(sensors == STAIR){
      motorStop();
      states = FORWARD;
    }
    else
      turning();
    break;


   default:
    states = FORWARD;
   
  }

 }
 
 void motorStop(){ //stops all the motors
    motorDriving(0, motorFLA, motorFLB);
    motorDriving(0, motorFRA, motorFRB);
    digitalWrite(motorBRA, LOW);
    digitalWrite(motorBRB, LOW);
    digitalWrite(motorBLA, LOW);
    digitalWrite(motorBLB, LOW);
 }
 void movingUpward(){ //Moves forward, slower back wheels to prevent collisions
   motorDriving(-255, motorFLA, motorFLB);
    motorDriving(100, motorFRA, motorFRB);
    digitalWrite(motorBRA, HIGH);
    digitalWrite(motorBRB, LOW);
    digitalWrite(motorBLA, HIGH);
    digitalWrite(motorBLB, LOW);
 }
 

void turning(){ //moves backwards while turning right when below threshold distance 
    if(usDistance < setDist){
    motorDriving(255, motorFLA, motorFLB);
    motorDriving(-255, motorFRA, motorFRB);
    digitalWrite(motorBRA, LOW);
    digitalWrite(motorBRB, HIGH);
    digitalWrite(motorBLA, LOW);
    digitalWrite(motorBLB, HIGH);
    }

else{ //turns right
    motorDriving(-255, motorFLA, motorFLB);
    motorDriving(100, motorFRA, motorFRB);
    digitalWrite(motorBRA, LOW);
    digitalWrite(motorBRB, HIGH);
    digitalWrite(motorBLA, HIGH);
    digitalWrite(motorBLB, LOW);
}

/*
    if(analogRead(ultrasonicFront) < setDist){
    motorDriving(255, motorFLA, motorFLB);
    motorDriving(-255, motorFRA, motorFRB);
    digitalWrite(motorBRA, LOW);
    digitalWrite(motorBRB, HIGH);
    digitalWrite(motorBLA, LOW);
    digitalWrite(motorBLB, HIGH); */

}
void altSensing(){
    
  //Checks to see if the current state of the tilt counter is the same as the inital state, it does this every 500 miliseconds for 2.5 seconds
  if(millis() - timer > 2500){
    timer = millis();

  }
  else if (millis() - timer  > 500){ 
    if(secondTilt != firstTilt){       
      tiltCounter += 1;
    } else {
      tiltCounter = 0;
    }
  }
  else if (tiltCounter >= 5){
    tiltCounter = 0;
    firstTilt = digitalRead(tiltPin);
    ground = !ground;
    /*The idea is that this would change the state as to change between whether ground is true (the robot is flat) 
    or ground is false (the robot is on the stairs)*/
  }
 }

 


