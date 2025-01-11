int motorA;
int motorB;

void setup(){
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
}

void loop(){
  motorDriving(255,motorA, motorB);
  delay(1000);
  motorDriving(-255,motorA, motorB);
  delay(1000);
  motorDriving(0,motorA, motorB);

}

int motorDriving(int speed, int motorA, int motorB){ //function for motor driving
 //Make sure speed is within the bounds
  if (speed < -255){
    speed = -255;
  }
  if (speed > 255){
    speed = 255;
  }
  
  //sets motors to spin forward, backwards or not at all depending on the sppeed
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

