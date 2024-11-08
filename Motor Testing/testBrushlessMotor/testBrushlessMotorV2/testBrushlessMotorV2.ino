// /*  Copyright (c) 2022 Lynxmotion
//  *  
//  *  author: Eric Nantel
//  *  maintainers: Eric Nantel
//  *  
//  *  Redistribution and use in source and binary forms, with or without
//  *  modification, are permitted provided that the following conditions are met:
//  *  
//  *    - Redistributions of source code must retain the above copyright
//  *      notice, this list of conditions and the following disclaimer.
//  *  
//  *    - Redistributions in binary form must reproduce the above copyright
//  *      notice, this list of conditions and the following disclaimer in the
//  *      documentation and/or other materials provided with the distribution.
//  *  
//  *    - Neither the name of the Lynxmotion nor the names of its
//  *      contributors may be used to endorse or promote products derived from
//  *      this software without specific prior written permission.
//  *  
//  *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  *  POSSIBILITY OF SUCH DAMAGE.
//  */

// // Include the PPM library
// #include "ppm.h"

// // PPM channel layout (update for your situation)
// #define PITCH       2

// // Variable to store the PPM values per channel
// short pitch;

// // consider channel at 0 until at least this much is sensed
// const int INPUT_DEADBAND = 10;             

// // Loop interval time
// const long interval = 10; //default 10
// unsigned long previousMillis = 0;

// void setup() {
//   Serial.begin(115200);

//   Serial.write("#254RESET\r");   
//   delay(2000);  // wait 2 sec for reboot

//   // Start the PPM function on PIN A3
//   ppm.begin(A3, false);

//   // LED Color
//   Serial.println("#254LED3"); // 3 = blue
// }

// void loop() {
//   // Interval at which the PPM & LSS Output are updated
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;
//     PPMupdate();
//     LSSupdate();
//   }
// }

// // Updating all the PPM values to each channel Variable
// void PPMupdate()
// { 
//   pitch = constrain(map(ppm.read_midstick(PITCH, INPUT_DEADBAND), -500, 500, -1023, 1023), -1023, 1023);
// }

// // Updating the positions of each LSS's
// void LSSupdate()
// { 
//   if ((pitch >=-1) && (pitch<= 1)){
//     Serial.println("#3RDM0");
//   }
//   else{
//     Serial.print("#3RDM");
//     Serial.println(pitch);
//   }

// }

// #include <Servo.h> 

// Servo esc;  // Create a servo object to control the ESC

// void setup() {
//   esc.attach(9);  // Attach the ESC signal pin to pin 9
//   // It's important to start with the ESC powered off or with the throttle at its lowest position
//   esc.writeMicroseconds(1000);  // Send a low signal to arm the ESC
//   delay(2000);  // Wait 2 seconds for the ESC to initialize
// }

// void loop() {
//   // The loop below sweeps the motor speed from minimum to maximum and back
//   for (int speed = 1000; speed <= 2000; speed += 10) { // Gradually increase speed
//     esc.writeMicroseconds(speed);
//     delay(15);
//   }
//   for (int speed = 2000; speed >= 1000; speed -= 10) { // Gradually decrease speed
//     esc.writeMicroseconds(speed);
//     delay(15);
//   }
// }


#include <Servo.h>

Servo esc;  // Create a servo object to control the ESC

void setup() {
  esc.attach(9);  // Attach the ESC signal pin to pin 9
  esc.writeMicroseconds(1000);  // Send a low signal to arm the ESC
  delay(2000);  // Wait 2 seconds for the ESC to initialize
}

void loop() {
  for (int speed = 1000; speed <= 1500; speed++) {  // Sweep from min to max
    esc.writeMicroseconds(speed);
    delay(20);
  }
  // esc.writeMicroseconds(2000);
  // delay(20);  // Wait for a second before repeating
}

// #include <Servo.h>

// Servo esc;  // Create a servo object to control the ESC

// void setup() {
//   esc.attach(9);  // Attach the ESC signal pin to pin 9
//   esc.writeMicroseconds(1000);  // Send a low signal to arm the ESC
//   delay(2000);  // Wait 2 seconds for the ESC to initialize
//   esc.writeMicroseconds(1500);  // Set a constant moderate speed
// }

// void loop() {
//   // The loop is intentionally left empty to maintain a constant speed
// }