#include <Wire.h> 
#include <MPU6050.h> 
MPU6050 sensor; 
void setup() { 
  Serial.begin(9600); 
  Wire.begin(); 
  sensor.initialize(); 
  
  if (sensor.testConnection()) 
  { Serial.println("Connected"); 
  } else 
  { Serial.println("Failed to connect"); 
  } 

  } void loop() { int16_t ax, ay, az; int16_t gx, gy, gz; 
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
  Serial.print("aX: "); 
  Serial.print(ax); 
  Serial.print(" | aY: "); 
  Serial.print(ay); 
  Serial.print(" | aZ: "); 
  Serial.print(az); 
  Serial.print(" | gX: "); 
  Serial.print(gx); 
  Serial.print(" | gY: "); 
  Serial.print(gy); 
  Serial.print(" | gZ: ");
   Serial.print(gz); 
   Serial.println(); 
   delay(500);
  }