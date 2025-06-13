#include <math.h>
#include <Servo.h>
#include <string.h>


int y;        //y-coordinate of desired direction
int x;        //x-coordinate of desired direction
float a = 8;  //length of first arm
float b = 8;  //length of second arm
float One;
float Two;  //Final position of the second servo
float Three;
float OneMain;  //Final position of first servo
float Conversion = 180 / M_PI;
Servo firstJoint;   //Servo for the first joint
Servo secondJoint;  //Servo for the second joint
int firstPos;       //position of the first servo
int secondPos;      //position of the second servo
bool coordinateComplete = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  firstJoint.attach(9);  //Setup the servos and which pins they will be attached to.
  secondJoint.attach(10);
  firstPos = 0;
  secondPos = 0;
  //firstJoint.write(firstPos);
  //secondJoint.write(secondPos);
}
void armMovement() {
  const uint32_t calculationDelay = 100;
  static enum { SERIAL_SEARCHING,
                SERIAL_SPLIT,
                ANGLE_CALCULATIONS } state = SERIAL_SEARCHING;

  switch (state) {
    case SERIAL_SEARCHING:
      if (Serial.available() > 0) {
        char Coord = Serial.read();
        state = SERIAL_SPLIT;
        break;


        case SERIAL_SPLIT:
          char token = strtok(Coord, ",");
          x = atoi(token);
          token = strtok(NULL, ",");
          y = atoi(token);
          delay(calculationDelay);
          state = ANGLE_CALCULATIONS;
          break;


        case ANGLE_CALCULATIONS:


          float angle2Denom = (2 * a * b);                   //Denominator of Cosine rule
          float angle2Num = (sq(x) + sq(y) - sq(a) - sq(b));  //Numerator of the Cosine rule
          angle2Rad = acosf(TopSecond , BottomSecond);
          float angle2Degree = Two * Conversion;  //Conversion from radians to degrees

          

        
          Three = ;     
          float angle1Denom = (a + (b * cosf(Two)));       //Denominator of Cosine rule
          float angle1Num = (b * sinf(Two));     //Numerator of the Cosine rule
          angle1Rad = atan2(y , x) - atan2(TopFirst, BottomFirst);  //Cosine rule
          float angle1Degree = angle1Rad * Conversion;  //Conversion from radians to degrees
          firstJoint.write(angle1Degree);//rotates the servo for the first joint
          secondJoint.write(angle2Degree);  //rotates the servo for the second joint
          state = SERIAL_SEARCHING;
          break;

        default:
          state = SERIAL_SEARCHING;
          break;
      }
  }
}


void loop() {
  armMovement();
}
