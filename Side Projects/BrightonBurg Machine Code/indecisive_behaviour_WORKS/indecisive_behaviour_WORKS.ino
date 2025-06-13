#include "Servo.h"

enum State_enum {BACKWARD, FORWARD,};
enum Sensors_enum {NONE, BOTH, };

static Sensors_enum sensors;
static State_enum state;
 
void motors_backward();
void motors_forward();


int leftSensor;
int rightSensor;
Servo leftServo;
Servo rightServo;

void setup()
{
  Serial.begin(9600);
  leftServo.attach(9);
  rightServo.attach(10);
  state = FORWARD;
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
  if (rightSensor < 860 && leftSensor < 860) 
  {
    sensors = NONE;
  }

  delay(10);
}
 
void state_machine_run(uint8_t sensors) //Goes forward til it senses an object, then it moves backwards until it no longer detects an object.
{
  switch(state)
  {
    case FORWARD:
      if(sensors == BOTH){
        motors_forward();
      }
      else {
        state = BACKWARD;
      }
         
      break;
       
    case BACKWARD:
      if(sensors == NONE){
        motors_backward();
      }
      else{
        state = FORWARD;
      }
      break;
  }
}

void motors_backward()
{
  //code for driving backward
  leftServo.write(0);
  rightServo.write(180);
  delay(1000);
}
 
void motors_forward()
{
  //code for driving forward  
  leftServo.write(180);
  rightServo.write(0);
  delay(1000);
}
 
