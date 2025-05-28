#include <Servo.h>
int pin = 3;
int pin2 = 4;
Servo servo;
Servo servo2;
int currentPositionX;
int currentPositionY;
int i;
int j;
void setup() {
servo.attach(pin);
servo2.attach(pin2);
move(20, servo);
currentPositionX = 20;
move(90, servo2);
currentPositionY = 90;
}

void move(int location, Servo servo){
  servo.write(location);
}
void smoothMove(int location, Servo servo, int speed, int currentPosition){

  if(currentPosition < location){
    for(i = currentPosition; i < location; i ++){
    move(i, servo);
    delay(speed);
    }
    currentPosition = i;
  }
  if(currentPosition > location){
    for(j = currentPosition; j > location; j --){
    move(j, servo);
    delay(speed);
   }
   currentPosition = j;
  }

}

void loop() {
  smoothMove(20, servo, 10, currentPositionX);
  smoothMove(75, servo2, 20, currentPositionY);
  delay(2000);
  smoothMove(90, servo, 10, currentPositionX);
  smoothMove(120, servo2, 20, currentPositionY);
  delay(2000);
  smoothMove(100, servo2, 20, currentPositionY);
  smoothMove(180, servo, 10, currentPositionX);
  delay(1000);
 

  
  /*
  move(20, servo);
  delay(1000);
  move(90, servo);
  delay(1000);
  move(180, servo);
  delay(1000);
  move(90, servo2);
  delay(1000);
  move(130, servo2);
  delay(1000);
  move(100, servo2);
  */
}

void yRotation(){
   smoothMove(180, servo, 20, currentPositionX);
   smoothMove(0, servo, 20, currentPositionX);
}
