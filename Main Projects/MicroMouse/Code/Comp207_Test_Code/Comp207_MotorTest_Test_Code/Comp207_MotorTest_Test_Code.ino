int motorRA = 1;
int motorRB = 0;
int motorLA = 3;
int motorLB = 2;
int motorSpeed = 30;

void setup() {
  Serial.begin(9600);
  pinMode(motorLA, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorRA, OUTPUT);
  pinMode(motorRB, OUTPUT);
}

void loop() {
     motorTest();
  }

void motorTest() {  //Tests the motors
  digitalWrite(motorRA, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLA, HIGH);
  digitalWrite(motorLB, LOW);
}