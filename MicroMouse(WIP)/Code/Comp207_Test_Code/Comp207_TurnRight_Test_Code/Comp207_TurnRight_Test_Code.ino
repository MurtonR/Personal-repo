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

void turnRight() {  //Turns right and then continues for a short time
  motorDriving(motorSpeed, motorLA, motorLB);
  motorDriving(-100, motorRB, motorRA);
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
     if (analogRead(leftTCRT) < 990 && analogRead(middleTCRT) < 990) {
      Serial.println(analogRead(leftTCRT));
      Serial.println(analogRead(middleTCRT));
      turnRight();
  }

}
