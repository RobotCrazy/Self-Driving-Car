#include <Servo.h>

Servo esc;  // Create a servo object to control the ESC

void setup() {
  esc.attach(9);  // Attach the ESC signal pin to pin 9
  esc.writeMicroseconds(2000);  // Send a low signal to arm the ESC
  delay(2000);  // Wait 2 seconds for the ESC to initialize
}

void loop() {
  esc.writeMicroseconds(2500);
  delay(5000);

  esc.writeMicroseconds(1500);  // Set a constant moderate speed
  delay(5000);  // Run the motor at this speed for 5 seconds

  esc.writeMicroseconds(1000);  // Turn off the motor by setting speed to minimum
  delay(5000);  // Motor stays off for 5 seconds

  // The loop will repeat this sequence indefinitely
}