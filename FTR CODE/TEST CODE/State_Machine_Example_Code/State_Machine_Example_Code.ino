#include <Servo.h>
enum states {IDLE, FOLLOW, THINKING, THROW}; //initalise state machine
enum vision {VOID, DETECTED, OBSERVED, HAT};// initalise state machine for sensing
static states currentState;  //make a copy
static vision visualSensor;  //make a copy
int servoYPin = 5;  //servo for vertical movement
int servoZPin = 3; //servo for horizontal movement
Servo y; //initalise servos
Servo z;
int currentPositionZ; //current position of z servo
int currentPositionY; //current position of y servo
int i;
int j;
char xCoord[9]; //unused array
char yCoord[9]; //unused array
int arrayPos = 0; //unused array
int arrayNum = 0; //unused array
int faceX = 0; //x coordinate of face
int faceY = 0; //y coordinate of face
String inputString; 
int seperator; //comma
int faceXmove;
int faceYmove;

void setup() {
Serial.begin(9600);
y.attach(servoYPin); //servo setup
z.attach(servoZPin);
move(90, y);  //set starting rotation of servos
currentPositionY = 90;
move(90, z);
currentPositionZ = 90;

}

void Hat(uint8_t sensed){
  
   currentState = IDLE;   //start robot in idle
   switch (currentState){
    case IDLE:
      if (sensed == VOID){
        smoothMove(90, z, currentPositionZ);  //code sets servos to look straight ahead
        smoothMove(90, y, currentPositionY);
      }
      if (sensed == DETECTED){
        currentState = FOLLOW;
      }
      if (sensed == HAT){
        currentState = THROW;
      }
      break;

    case FOLLOW:
    if (sensed != DETECTED){
      
       currentState = IDLE;
    }
    else{
      char byte = Serial.read(); //set byte from serial communication
      Serial.print(byte); //print byte
      getCoordinates(byte); //run function to get coordinates
    }
      break;
    case THINKING:
      //state for time expensive code such as what audio to play
    case THROW:
    if (sensed != THROW){
      currentState = IDLE;
    }
    else{
      smoothMove(0,z, currentPositionZ);
      smoothMove(180,y, currentPositionY);  //sharp movement forward using move should fling hat off
      move(0,y);
      currentPositionY = 0;
    }
    break;
  }
}


void move(int location, Servo servo){
  servo.write(location);   //quick movement
}


void smoothMove(int location, Servo servo , int currentPosition){  //increments movement between currentpoisiton of servo and desired position

  if(currentPosition < location){
    for(i = currentPosition; i <= location; i ++){   
    move(i, servo); 
    Serial.println(i);
    delay(10);
    }
    currentPosition = i;    
  }
  else if(currentPosition > location){
    for(j = currentPosition; j >= location; j --){
    move(j, servo);
    Serial.println(j);
    delay(10);
   }
   currentPosition = j;
  }
  else{

  }
}

void getCoordinates(char byte){  //runs for every byte in the serial communication, outputs whole coordinates
  
   if (byte == 'n') { //checks to see if endline character is found
     
      seperator = inputString.indexOf(','); //sets seperator to be the position in the string where the comma is present
      if (seperator != -1) { // runs if comma is present 
          faceX = inputString.substring(0, seperator).toInt();  //sets the x coordinate to be all the numbers before the comma and converts to int
          faceY = inputString.substring(seperator + 1).toInt(); //sets the y coordinate to be all the numbers after the comma and converrts to int
          faceXmove = map(faceX, 450, -60, 180,0 );  //maps x and y to the servo range
          faceYmove = map(faceY, 400, 0, 180,0 );
          move(faceXmove,z); //moves servos
          move(faceYmove,y);
          Serial.println (" x: " + String(faceX) + ", y: " + String(faceY)); //prints full coordinates. 
      }
      inputString = ""; 
    }
  else { //adds each part to the input string when the endline character is not found
    inputString += byte; 
  }
}

void loop() {  
  //visualSensor = VOID;
  
//data from python needs to be organised like this ___,___n    where the blanks are the x and y values, the n is there to end the communication
  if (Serial.available() > 0 && ) { //checks to see if there is any serial communication
    visualSensor = DETECTED;
   

}
Hat(visualSensor);
  //smoothMove(80, z, currentPositionZ);
  //smoothMove(80, y , currentPositionY);
  //delay(1000);
  //smoothMove(0, z, currentPositionZ);
  //smoothMove(0, y, currentPositionY);
  //delay(1000);
  //To Do:
  //code here should be the sensing, so the cameras and hat sensing
}

void yRotation(){    //code to be expanded upon
   smoothMove(180, y, currentPositionY);
   smoothMove(0, y, currentPositionY);
}