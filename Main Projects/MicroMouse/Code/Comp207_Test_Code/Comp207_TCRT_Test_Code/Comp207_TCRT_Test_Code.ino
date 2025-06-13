int blueLED = 19;
int redLED = 18;
int yellowLED = 20;
int leftTCRT = 26;
int middleTCRT = 28;
int rightTCRT = 27;

void setup() {
  Serial.begin(9600);
  pinMode(leftTCRT, INPUT);
  pinMode(middleTCRT, INPUT);
  pinMode(rightTCRT, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
 
}

void loop() {
   testTCRT();
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