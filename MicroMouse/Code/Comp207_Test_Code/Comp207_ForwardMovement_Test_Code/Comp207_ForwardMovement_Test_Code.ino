int blueLED = 19;
int redLED = 18;
int yellowLED = 20;
int leftTCRT = 26;
int middleTCRT = 28;
int rightTCRT = 27;
int motorRA = 1;
int motorRB = 0;
int motorLA = 3;
int motorLB = 2;
int motorSpeed = 30;

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
void forwardMovement() {  //Moves the mouse forwards should accomodate to ensure it stays in the middle of the path
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

void loop() {
     forwardMovement();
  }

