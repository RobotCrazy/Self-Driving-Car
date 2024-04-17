#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "PWMServo.h"

#define motorPin 8
#define servoPin 10

//Servo servo1;
Servo motor1;

void setup()
{
  pinMode(motorPin, OUTPUT);
  // motor1.attach(motorPin);
  Serial.begin(115200);
  delay(8000);

  // servo1.attach(servoPin);  
}
void loop() {
  for(int i = 0; i <= 255; i++) {
    analogWrite(motorPin, i);
    delay(50);
    Serial.println(i);
  }

  for(int i = 255; i >= 0; i--) {
    analogWrite(motorPin, i);
    delay(50);
    Serial.println(i);
  }

  analogWrite(motorPin, 0);
  delay(5000);
}

const int servoStart = 80;
const int servoEnd = 110;
