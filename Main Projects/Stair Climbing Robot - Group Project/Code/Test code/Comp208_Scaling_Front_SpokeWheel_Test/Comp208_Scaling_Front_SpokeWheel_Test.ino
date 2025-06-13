//int variables for right spoke wheel
int motorFRA= 3;
int motorFRB = 11;

//int variables for left spoke wheel 
int motorFLA;
int motorFLB;

// Takes a and b pin of motor and sets to specific speed
void motorDriving(int speed, int motorA, int motorB){ 
  if (speed < -255){
    speed = -255;            // if speed goes below -255 bring back to -255
  }
  if (speed > 255){
    speed = 255;             // if speed goes above 255 bring back to 255
  }
  
  //sets motors to spin forward, backwards or not at all
  if(speed > 0){
    analogWrite(motorA, -speed);
    analogWrite(motorB, speed);
  }
   if(speed < 0){
    analogWrite(motorA, speed);
    analogWrite(motorB, -speed);
  }
   if(speed == 0){
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
  }
   //analogWrite(motorE, speed);
}

// sets both spoke wheels to movbe forward
void movingUpward(){
    motorDriving(180, motorFRB, motorFRA);
    motorDriving(180, motorFLB, motorFLA);
    
 }
// unsures all pins output
void setup() {
  pinMode(motorFLA,OUTPUT);
  pinMode(motorFLB,OUTPUT);
  pinMode(motorFRA,OUTPUT);
  pinMode(motorFRB,OUTPUT);
}

void loop() {
  movingUpward();

}
