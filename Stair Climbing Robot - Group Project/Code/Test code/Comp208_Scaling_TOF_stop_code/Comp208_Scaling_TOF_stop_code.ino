#include <Wire.h>           // allow use of laser sensor
#include <VL53L0X.h>          // library for laser range finder
#include <Encoder.h>

// Variables for motor1
int encoderA = 0;
int encoderB = 0;
int motorA = 5;
int motorB = 6;
int motorE = 0;
// Variables for motor2
int encoder2A = 0;
int encoder2B = 0;
int motor2A = 10;
int motor2B = 11;
int motor2E = 0;
// Variable for back motors
int motorNA = 3;
int motorNB = 2;
int motorNE = 0;
int motor2NA = 13;
int motor2NB = 12;
int motor2NE = 0;

// Set up encoder for both wheels
Encoder wheelSet1(encoderA, encoderB);
Encoder wheelSet2(encoder2A, encoder2B);

// Laser range finder declaration
VL53L0X sensor;

// Simplified and easier to call function for reading the distance
int readDistance() {
  return sensor.readRangeSingleMillimeters();  // Return distance in millimeters
}

void motorDriving(int speed, int motorA, int motorB, int motorE) {
  // Ensure speed is within bounds
  if (speed < -255) {
    speed = -255;
  }
  if (speed > 255) {
    speed = 255;
  }

  // Set motors to spin forward, backward, or not at all
  if (speed > 0) {
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
  } else if (speed < 0) {
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
  } else {
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, LOW);
  }
}

void setup() {
  // Set the pin modes of the motor pins and encoder pins
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(motorE, OUTPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(encoder2A, INPUT);
  pinMode(encoder2B, INPUT);
  pinMode(motorNA, OUTPUT);
  pinMode(motorNB, OUTPUT);
  pinMode(motor2NA, OUTPUT);
  pinMode(motor2NB, OUTPUT);

  Serial.begin(9600);

  // Initialize the laser rangefinder
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);  // Set timeout for laser sensor
}

void loop() {
  // Read distance from the laser sensor using the simplified function
  int distance = readDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" mm");

  // Basic behavior: Stop motors if an object is closer than 200mm
  if (distance < 200) {
    motorDriving(0, motorA, motorB, motorE);
    motorDriving(0, motor2A, motor2B, motor2E);
    digitalWrite(motorNA, LOW);
    digitalWrite(motorNB, LOW);
    digitalWrite(motor2NA, LOW);
    digitalWrite(motor2NB, LOW);
    Serial.println("Too close to wall! Stopping motors.");
  } else {
    // Move forward
    motorDriving(100, motorA, motorB, motorE);
    motorDriving(100, motor2A, motor2B, motor2E);
    digitalWrite(motorNA, HIGH);
    digitalWrite(motorNB, LOW);
    digitalWrite(motor2NA, HIGH);
    digitalWrite(motor2NB, LOW);
  }

  delay(100); // Small delay for stability
}
