//pins for the LED's
int blueLED = 19;
int redLED = 18;
int yellowLED = 20;

//pins for the TCRT
int leftTCRT = 26;
int middleTCRT = 28;
int rightTCRT = 27;

//Variables for the motors
int motorRA = 1;
int motorRB = 0;
int motorLA = 3;
int motorLB = 2;
int motorSpeed = 30;

unsigned long timer;

//Initialise mouse states
enum Mouse_enum { FORWARD,
                  TURNRIGHT,
                  TURNLEFT,
                  CROSSROAD };
enum Sensor_enum { RIGHT,
                   LEFT,
                   MIDDLE,
                   NONE };
static Mouse_enum mouse;
static Sensor_enum sensor;

void motorDriving(float speed, int motorA, int motorB) {  //function for motor driving
                                                        //Make sure speed is within the bounds
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 255) {
    speed = 255;
  }

  //sets motors to spin forward, backwards or not at all depending on the speed
  if (speed > 0) {
    analogWrite(motorA, -speed);
    analogWrite(motorB, speed);
  }
  if (speed < 0) {
    analogWrite(motorA, speed);
    analogWrite(motorB, -speed);
  }
  if (speed == 0) {
    analogWrite(motorA, 0);
    analogWrite(motorB, 0);
  }
}

void turnLeft() {  //Turns left and then continues for a short time
  motorDriving(-30 , motorLB, motorLA);
  motorDriving(motorSpeed, motorRA, motorRB);
}
void turnRight() {  //Turns right and then continues for a short time
  motorDriving(motorSpeed, motorLA, motorLB);
  motorDriving(-47, motorRB, motorRA);
}
void wallInfront() {  //Decides which way to turn depending on the closest distance and then turns
  if (analogRead(leftTCRT) < analogRead(rightTCRT)) {
    motorDriving(-motorSpeed, motorLB, motorLA);
    motorDriving(10, motorRA, motorRB);
    delay(250);
  } else {
    motorDriving(10, motorLA, motorLB);
    motorDriving(-motorSpeed, motorRB, motorRA);
    delay(250);
  }
}
void forwardMovement() {  //Moves the mouse forwards should accomodate to ensure it stays in the middle of the path by adjusting the amount of power to each wheel depending on the distance
  float right = map(analogRead(leftTCRT), 800, 1030, 20,30 );
  float left = map(analogRead(rightTCRT), 800, 1030, 20,30);
  Serial.println(left);
  Serial.println(right);
  motorDriving(left, motorLA, motorLB);
  motorDriving(right, motorRA, motorRB);
}


void setup() {
  Serial.begin(9600);
  pinMode(leftTCRT, INPUT);
  pinMode(middleTCRT, INPUT);
  pinMode(rightTCRT, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(motorLA, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorRA, OUTPUT);
  pinMode(motorRB, OUTPUT);
}

void mouseStates(uint8_t Sensor_enum) {//each state has a LED that only lights up when it is active
  switch (mouse) {
    case FORWARD:  //Set the state depending on which direction walls are detected in, if there are no walls go forward
      if (sensor == LEFT) {
        timer = millis();
        mouse = TURNRIGHT;
      }
      if (sensor == MIDDLE) {
        mouse = CROSSROAD;
      }
      if (sensor == RIGHT) {
        timer = millis();
        mouse = TURNLEFT;
      }
      if (sensor == NONE) {
        forwardMovement();
      }
      break;
    
    case CROSSROAD:
      if (sensor != MIDDLE) {  //For each of these states a corrosponding LED will light up to signify that they are the active state
        mouse = FORWARD;
        digitalWrite(blueLED, LOW);
      } else {
         digitalWrite(blueLED, HIGH);
        wallInfront();
       
      }
      break;

    case TURNLEFT:  //The timer means that the robot will turn for a specified amount of time, allowing it to make corners with less collisions
      if (millis() - timer >= 140) {
        digitalWrite(redLED, LOW);
        mouse = FORWARD;

      } else {
        digitalWrite(redLED, HIGH);
        turnLeft();
      }
      break;

    case TURNRIGHT:
      if (millis() - timer >= 140) {
        digitalWrite(yellowLED, LOW);
        mouse = FORWARD;
      } else {
        digitalWrite(yellowLED, HIGH);
        turnRight();
      }
      break;
  }
}


void loop() {
  /*
  testTCRT();
  motorTest();
  testLED();
  mouseStates(sensor);
  sensing();
  */
  delay(100);
  Serial.println(analogRead(middleTCRT)); //reads TCRTs and prints it to the serial monitor
  Serial.println(analogRead(leftTCRT));
  Serial.println(analogRead(rightTCRT));
  if ((analogRead(leftTCRT) < 990) && (analogRead(middleTCRT) < 990)) { //sets the state of sensor to LEFT,RIGHT,MIDDLE or NONE
    sensor = LEFT;
  }
  else if ((analogRead(rightTCRT) < 990) && (analogRead(middleTCRT) < 990)) {
    sensor = RIGHT;
  }
  else if (analogRead(middleTCRT) < 700) {
    Serial.println(analogRead(middleTCRT));
    sensor = MIDDLE;
  }
    else {
    sensor = NONE;
  }

  mouseStates(sensor); //Run state machine for the mouse states
}


//Test code
/*
void testLED() {  //Tests the LED's
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(1000);
  digitalWrite(redLED, LOW);
  delay(1000);
  digitalWrite(yellowLED, LOW);
  delay(1000);
  digitalWrite(blueLED, LOW);
  delay(1000);
}
void testTCRT() {  //Tests the TCRT's by turning LED's on if they detect something
  if (analogRead(leftTCRT) < 900) {
    digitalWrite(redLED, HIGH);
  }
  if (analogRead(leftTCRT) > 900) {
    digitalWrite(redLED, LOW);
  }

  if (analogRead(middleTCRT) < 900) {
    digitalWrite(yellowLED, HIGH);
  }
  if (analogRead(middleTCRT) > 900) {
    digitalWrite(yellowLED, LOW);
  }

  if (analogRead(rightTCRT) < 900) {
    digitalWrite(blueLED, HIGH);
  }
  if (analogRead(rightTCRT) > 900) {
    digitalWrite(blueLED, LOW);
  }
}
void motorTest() {  //Tests the motors
  digitalWrite(motorRA, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLA, HIGH);
  digitalWrite(motorLB, LOW);
}

void sensing() {  //Sets the state of the sensors, currently unused
  if (analogRead(leftTCRT) && analogRead(middleTCRT) < 950) {
    sensor = LEFT;
  }
  if (analogRead(rightTCRT) && analogRead(middleTCRT) < 950) {
    sensor = RIGHT;
  }
  if (analogRead(middleTCRT) < 800) {
    sensor = MIDDLE;
  }

  else {
    sensor = NONE;
  }
}

void movement() { //Basic Movement function, currently unused

  if (analogRead(leftTCRT) && analogRead(middleTCRT) < 970) {
    turnRight();
  }
  if (analogRead(rightTCRT) && analogRead(middleTCRT) < 970) {
    turnLeft();
  }
  else if (analogRead(middleTCRT) < 900) {
    wallInfront();
  } else {
    forwardMovement();  //Moves the mouse forwards should accomodate to ensure it stays in the middle of the path
  }
}
*/