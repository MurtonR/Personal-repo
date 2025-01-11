#include "Servo.h"

enum State_enum {SEARCHING, FORWARD};
enum Sensors_enum {NONE, BOTH, CLOSE};

static Sensors_enum sensors;
static State_enum state;
 
void motors_searching();
void motors_forward();
void motors_stop();

int leftSensor;
int rightSensor;
Servo leftServo;
Servo rightServo;

void setup()
{
  Serial.begin(9600);
  leftServo.attach(9);
  rightServo.attach(10);
}
 
void loop()
{
  state_machine_run(sensors); 
  
  leftSensor = analogRead(A1); // Set the pins to your sensor pin
  rightSensor = analogRead(A2);
  Serial.println(leftSensor);
  Serial.println(rightSensor);
  
  if (rightSensor > 900 && leftSensor > 900) 
  {
    sensors = BOTH;
  }
  if (rightSensor < 820 && leftSensor < 820) 
  {
    sensors = NONE;
  }
    if (rightSensor < 450 && leftSensor < 450) 
  {
    sensors = CLOSE;
  }

  delay(10);
}
 
void state_machine_run(uint8_t sensors) 
{
  switch(state)
  {
    case SEARCHING:
      if(sensors == NONE){
        motors_forward();
        state = FORWARD;
      }
      else{
        motors_searching();
      
      }
      break;
       
    case FORWARD:
      if(sensors == BOTH){
        motors_searching();
        state = SEARCHING;
      }
      else if (sensors == CLOSE){
        motors_stop();
      }
      break;
 

  }
}

void motors_stop(){
  leftServo.write(90);
  rightServo.write(90);
  delay(1000);
}
void motors_searching()
{
  //code for stopping motors
  leftServo.write(0);
  rightServo.write(180);
  delay(500);
  leftServo.write(180);
  rightServo.write(0);
  delay(1000);
}
void motors_forward()
{
  //code for driving forward  
  leftServo.write(180);
  rightServo.write(0);
  delay(1000);
}
 
