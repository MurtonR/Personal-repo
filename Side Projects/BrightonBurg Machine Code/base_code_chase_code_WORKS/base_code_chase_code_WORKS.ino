#include "Servo.h"

enum State_enum {STOP, FORWARD, ROTATE_RIGHT, ROTATE_LEFT};
enum Sensors_enum {NONE, SENSOR_RIGHT, SENSOR_LEFT, BOTH};

static Sensors_enum sensors;
static State_enum state;
 
void motors_stop();
void motors_forward();
void motors_right();
void motors_left();

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
  
  leftSensor = analogRead(A0); // Set the pins to your sensor pin
  rightSensor = analogRead(A1);
  Serial.println(leftSensor);
  Serial.println(rightSensor);
  if (leftSensor > 900) //Values are arbitrary - adjust for your sensors
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
  if (rightSensor < 870 && leftSensor < 870) 
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
      if(sensors == BOTH){
        motors_forward();
        state = FORWARD;
      }
      else if(sensors == SENSOR_RIGHT){
        motors_right();
        state = ROTATE_RIGHT;
      }
      else if(sensors == SENSOR_LEFT){
        motors_left();
        state = ROTATE_LEFT;
      }
      else{
        motors_stop();
      }
      break;
       
    case FORWARD:
      if(sensors != BOTH){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_RIGHT:
      if( sensors != SENSOR_RIGHT){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_LEFT:
      if(sensors != SENSOR_LEFT)
      {
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
 
void motors_right()
{
  //code for turning right
  leftServo.write(180);
  rightServo.write(90);
  delay(1000);
}
 
void motors_left()
{
  //code for turning left
  leftServo.write(90);
  rightServo.write(0);
  delay(1000);
}
