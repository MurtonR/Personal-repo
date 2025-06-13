#include "Servo.h"

enum State_enum {BACKWARD, FORWARD, ROTATE_RIGHT, ROTATE_LEFT};
enum Sensors_enum {NONE, SENSOR_RIGHT, SENSOR_LEFT, BOTH};

static Sensors_enum sensors;
static State_enum state;

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

  if (leftSensor > 50) //Values are arbitrary - adjust for your sensors
  {
    sensors = SENSOR_LEFT;
  }
  if (rightSensor > 50) 
  {
    sensors = SENSOR_RIGHT;
  if (rightSensor > 50 && leftSensor > 50) 
  {
    sensors = BOTH;
  }
  if (rightSensor < 10 && leftSensor < 10) 
  {
    sensors = NONE;
  }

  delay(10);
}
}
void state_machine_run(uint8_t sensors) 
{
  switch(state)
  {
    case FORWARD:
        leftServo.write(180);
        rightServo.write(0);
        //motors_forward();
        delay(1000);
        state = ROTATE_LEFT;
         Serial.println("forward");
        break;
    case ROTATE_LEFT:
        leftServo.write(90);
        rightServo.write(0);
        //motors_left();
        delay(1000);
        state = ROTATE_RIGHT;
        Serial.println("left");
        break;
    case ROTATE_RIGHT:
        leftServo.write(180);
        rightServo.write(90);
       // motors_right();
        delay(1000);
        state = BACKWARD;
        
        Serial.println("right");
        break;
    case BACKWARD:
        leftServo.write(0);
        rightServo.write(180);
         // motors_backward();
        delay(1000);
        state = FORWARD;
        Serial.println("backward");
        break;
         default:
          state = FORWARD;  //Default State
          break;
  }
}   
       
