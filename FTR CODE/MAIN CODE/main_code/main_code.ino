#include <Servo.h>
#include "Arduino.h"
//#include "DFRobotDFPlayerMini.h"

#define LEDPin 7 //unused at the moment
#define eButton 2
#define eMagnet 6
#define eMagnet2 7
#define FPSerial Serial1

int timer; //Initialise timer 
#define LDRPin A0
enum states {IDLE, FOLLOW, THINKING, THROW}; //initalise state machine
enum vision {VOID, DETECTED, OBSERVED, HAT};// initalise state machine for sensing
static states currentState;  //make a copy
static vision visualSensor;  //make a copy

int servoEyePin = 9;  //servo for eye movement
int servoY2Pin = 5; //servo for vertical movement
int servoZPin = 3; //servo for horizontal movement
Servo eye; //initalise servos
Servo y2;
Servo z;
int currentPositionEye;
int currentPositionZ; //current position of z servo
int currentPositionY; //current position of y servo
int i;
int j;
char xCoord[9]; //unused array
char yCoord[9]; //unused array
int arrayPos = 0; //unused array
int arrayNum = 0; //unused array
int faceZ = 0; //x coordinate of face
int faceY = 0; //y coordinate of face
String inputString; 
int seperator; //the seperator is a comma ","
int faceZmove;
int faceYmove;
int faceY2move;
char bytes;
bool throwing = false;


//LDR and Electromagnet code modified from Charlie's test code
long LDRValue = 1000;
int bMode = 0;
int lastBMode = 0;
int magnetMode = 1;

void setup() {
//Serial Setup

Serial.begin(9600);
//LDR and Electromagnets
pinMode(LDRPin, INPUT);

pinMode(LEDPin, OUTPUT);
pinMode(eButton, INPUT);
pinMode(eMagnet, OUTPUT);
pinMode(eMagnet2, OUTPUT);
digitalWrite(eMagnet, 1);
digitalWrite(eMagnet2, 1);

//servo setup
eye.attach(servoEyePin); 
y2.attach(servoY2Pin);
z.attach(servoZPin);
//set starting rotation of servos
currentPositionY = 450;
move(90 , eye);
move(80 , z);
move(55 , y2);
currentPositionZ = 80;
//start robot in idle so there is no movement
currentState = IDLE;   

//Initalise timer for idle movement
 int timer = millis();


//Speaker module demo code 
/*
  if (!myDFPlayer.begin(FPSerial, true, true)) {  // Use Serial1 to communicate with DFPlayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while (true) {
      delay(0);  // Infinite loop to halt the program
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(10);  // Set volume (0-30)
  myDFPlayer.play(1);     // Play first MP3
  */
}


//Main state machine
void RobotHead(uint8_t sensed){
  
  
   switch (currentState){  
    case IDLE:  //Intermediate state
      if (sensed == VOID){
       //Do nothing,  this is to prevent it from moving in between serial communications.
      }
      if (sensed == DETECTED){ 
        currentState = FOLLOW;
      }
      if (sensed == HAT){
        currentState = THROW;
      }
      break;


    case FOLLOW: //Head following state
    if (sensed != DETECTED){
      
       currentState = IDLE;
    }
    else{
     
      Serial.print(bytes); //print byte
      getCoordinates(bytes); //run function to get coordinates
    }
      break;

    case THINKING: //state for time expensive code like speakers

    case THROW: //State for throwing the hat when the LDR is covered
    if (sensed != THROW){
      currentState = IDLE;
    }
    else{
    throwfunc();
    }
    break;
  }
}




//Movement

void move(int location, Servo servo){
  servo.write(location);   //quick movement
  //currentPosition = location;
}


void smoothMove(int location, Servo servo , int currentPosition){  //increments movement between currentpoisiton of servo and desired position

  if(currentPosition < location){ //When current position is less than the desired location, increase the servo rotation by 1 for each loop
    for(i = currentPosition; i <= location; i ++){   
    move(i, servo); 
    Serial.println(i);
    delay(40);
    }
    currentPosition = i;    
  }
  else if(currentPosition > location){ //When current position is greater than the desired location, decrease the servo rotation by 1 for each loop 
    for(j = currentPosition; j >= location; j --){
    move(j, servo);
    Serial.println(j);
    delay(40);
   }
   currentPosition = j;
  }
  else{

  }
}

void throwfunc(){ //Function for throwing the hat
  throwing = true; //ensures this only runs once
  digitalWrite(eMagnet, 0); //connect electromagnets
  digitalWrite(eMagnet2, 0);
  delay(1000);
  move(10,y2); //Move neck backwards
  digitalWrite(eMagnet, 1); //Disconnect electromagnets
  digitalWrite(eMagnet2, 1);
  delay(1000);
  move(140,y2); //Move neck forwards
  delay(1000);
  throwing = false; 
}
//Coordinate cleaning

void getCoordinates(char bytes){  //runs for every byte in the serial communication, outputs whole coordinates
  
   if (bytes == 'n') { //checks to see if endline character is found
     
      seperator = inputString.indexOf(','); //sets seperator to be the position in the string where the comma is present
      if (seperator != -1) { // runs if comma is present 
          faceZ = inputString.substring(0, seperator).toInt();  //sets the x coordinate to be all the numbers before the comma and converts to int
          faceY = inputString.substring(seperator + 1).toInt(); //sets the y coordinate to be all the numbers after the comma and converrts to int
          faceZmove = map(faceZ, 540, -70, 0,160 );  //maps x and y to the servo range
          faceY2move = map(faceY, 300, 0, 0,120 );
          move(faceZmove,z); //moves servos
          move(faceY2move,y2);
          Serial.println (" x: " + String(faceZ) + ", y: " + String(faceY)); //prints full coordinates. 
      }
      inputString = ""; 
    }
  else { //adds each part to the input string when the endline character is not found
    inputString += bytes; 
  }
}

void loop() {  
  
 LDRValue = analogRead(LDRPin); //Get LDR value
 Serial.println(LDRValue);
  
//data from python needs to be organised like this ___,___n    where the blanks are the x and y values, the n is there to end the communication
  if (Serial.available() > 0 && LDRValue > 100 && throwing == false){ //when serial available, LDR is not covered and the hat is not currently being thrown off
    bytes = Serial.read(); //set byte from serial communication
    timer = millis(); //set timer to determine the time since last tracking
    visualSensor = DETECTED;
  
  }
  
  if (Serial.available() > 0 && LDRValue < 100 && throwing == false){ //When serial available, LDR is covered and the hat is not currently being thrown off
    bytes = Serial.read(); //set byte from serial communication
    timer = millis(); //set timer to determine the time since last tracking
    visualSensor = HAT;
  }


  if( millis() - timer> 5000){ //After 5 seconds run idle movement of eyes
    move(30, eye); //reset eye position
    currentPositionEye = 30; 
    smoothMove(180, eye, currentPositionEye); //Moves from 0 - 180
    currentPositionEye = 180;
    smoothMove(30, eye , currentPositionEye); //Moves from 180 - 0
    
  }

 
  RobotHead(visualSensor); //calls the state machine
}
