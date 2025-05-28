int blueLED = 19;
int redLED = 18;
int yellowLED = 20;

void setup() {
  Serial.begin(9600);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}

void loop() {
     testLED();
  }


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