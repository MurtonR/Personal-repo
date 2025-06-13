int tiltSensorPin = 3;
int redLED = 4;
int blueLED = 5;

void setup() {
  pinMode(tiltSensorPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);


}

void loop() {
  if(digitalRead(tiltSensorPin) == 0){
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED,LOW);
  }
   else{
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED,HIGH);
  }

}
