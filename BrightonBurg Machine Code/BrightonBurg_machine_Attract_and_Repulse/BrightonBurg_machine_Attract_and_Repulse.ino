#include "Servo.h"

enum State_enum {STOP, FORWARD};
enum Sensors_enum {NONE, SENSOR_RIGHT, SENSOR_LEFT, BOTH};

static Sensors_enum sensors;
static State_enum state;
 
void motors_stop();
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
}
 
void loop()
{
  state_machine_run(sensors); 
  
  leftSensor = analogRead(A1); // Set the pins to your sensor pin
  rightSensor = analogRead(A2);
  Serial.println(leftSensor);
  Serial.println(rightSensor);
  if (leftSensor > 930) //Values are arbitrary - adjust for your sensors
  {
    sensors = SENSOR_LEFT;
  }
  if (rightSensor > 930) 
  {
    sensors = SENSOR_RIGHT;
  }
  if (rightSensor > 930 && leftSensor > 930) 
  {
    sensors = BOTH;
  }
  if (rightSensor < 880 && leftSensor < 880) 
  {
    sensors = NONE;
  }

  delay(10);
}
 
void state_machine_run(uint8_t sensors) //base code that should avoid light
{
  switch(state)
  {
    case STOP:
      if(sensors != NONE){
        motors_forward();
        state = FORWARD;
      }
      else{
        motors_stop();
      
      }
      break;
       
    case FORWARD:
      if(sensors == NONE){
        motors_stop();
        state = STOP;
      }
      break;
 

  }
}
 
void motors_stop()
{
  //code for stopping motors
  leftServo.write(90);
  rightServo.write(90);
  delay(1000);
}
 
void motors_forward()
{
  //code for driving forward  
  leftServo.write(180);
  rightServo.write(0);
  delay(1000);
}
 
