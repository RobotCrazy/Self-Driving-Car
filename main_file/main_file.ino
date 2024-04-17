#include "pid_control.hpp"
#include "kalman_estimator.hpp"
#include <Servo.h>

#define motorPin 8
#define servoPin 10
#define LEDpin 9

typedef void (*HandlerFunction) (String incomingData);

Servo servo1;
float headingAngle = 0, deltaDistance = 0;
int startRobot = 0;

const int SERVO_MIN = 86, SERVO_MAX = 130;

//Handler Functions
void handleRequestedMotorSpeed(String incomingData);
void handleRequestedServoAngle(String incomingData);
void handleHeadingAngle(String incomingData);
void handleDeltaDistance(String incomingData);
void handleStartRobot(String incomingData);

String inputStrings[] = {"head", "dd", "sr"};
HandlerFunction handlers[] = {handleHeadingAngle, handleDeltaDistance, handleStartRobot};

int findHandlerIndex(String inputStr) {
  int equalsIndex = inputStr.indexOf("=");
  String inputStrCode = inputStr.substring(0, equalsIndex);

  int numHandlers = sizeof(inputStrings) / sizeof(inputStrings[0]);
  for(int i = 0; i < numHandlers; i++) {
    if(inputStrCode.equals(inputStrings[i])) {
      return i;
    }
  }

  return -1;
}

void clearSerialBuffer() {
  char throwAwayData;
  if(Serial.available() >= 32) {
    for(int i = 0; i < 32; i++) {
      throwAwayData = Serial.read();
    }
  }
}

void handleCommand() {
  if(Serial.available()) {
    String incomingData = Serial.readStringUntil('\n');
    incomingData.toLowerCase();

    int index = findHandlerIndex(incomingData);

    if(index > -1) {
      HandlerFunction handlerFunc = handlers[index];
      handlerFunc(incomingData);
    }

    Serial.print("Done: ");
    Serial.println(incomingData);
  }
}

void handleHeadingAngle(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  String valStr = incomingData.substring(equalsIndex + 1);
  float val = valStr.toFloat();

  // Serial.print(incomingData.substring(0, equalsIndex+1));
  // Serial.println(val);

  headingAngle = val;

  // for(int i = 0; i < 10; i++) {
  //   digitalWrite(12, HIGH);
  //   delay((int)headingAngle);
  //   digitalWrite(12, LOW);
  //   delay((int)headingAngle);
  // }
}

void handleStartRobot(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  String valStr = incomingData.substring(equalsIndex + 1);
  int val = valStr.toInt();

  // Serial.print(incomingData.substring(0, equalsIndex+1));
  // Serial.println(val);

  startRobot = val;
  if (val) {
    analogWrite(motorPin, 255);
  }
  else {
    analogWrite(motorPin, 0);
  }
}

void handleDeltaDistance(String incomingData) {
  int equalsIndex = incomingData.indexOf("=");
  String valStr = incomingData.substring(equalsIndex + 1);
  int val = valStr.toInt();

  // Serial.print(incomingData.substring(0, equalsIndex+1));
  // Serial.println(val);

  // Serial.println(Serial.available());

  deltaDistance = val; 

  if (val > 0) {
    //analogWrite(motorPin, 255);
    digitalWrite(LEDpin, HIGH);
  }
  else {
    //analogWrite(motorPin, 0);
    digitalWrite(LEDpin, LOW);
  }
}

KAL_ESTIMATOR k_est;
PID_CONTROLLER pid;
float k_weight = 0.5;
float d_weight = 0.5;
float final_controller_output;
float servo_input;

void setup() {
  Serial.setTimeout(2);
  Serial.begin(115200);
  // setup for gyro
  // k_est.beginDevice();
  // k_est.gyroCal();
  char throwAwayData;
  while(Serial.available() > 0) {
    throwAwayData = Serial.read();
  }
  
  pinMode(motorPin, OUTPUT); //Set up motor pin
  delay(4000);
  analogWrite(motorPin, 180);
  pinMode(LEDpin, OUTPUT);
  servo1.attach(servoPin); //Set up servo pin
}

void loop() {  
  
  handleCommand();

  clearSerialBuffer();
  // get yaw rate from gyro
  // k_est.calculate_gyro_rate();

  // if (true) { // this checks if a heading measurement is available from the camera

  //   // replace with Jetson deltax
  //   int deltax = deltaDistance;

  //   // replace function argument with Jetson heading measurement
  //   k_est.get_camera_angle(headingAngle);

  //   // calculate kalman filter angle with new Jetson measurement and gyro yaw rate
  //   k_est.calculate_posteriori_angle();

  //   // execute outer PID loop
  //   pid.output_target_pitch_rate(k_est.return_posteriori_angle(), 
  //                              deltax, k_weight, d_weight);
  // }

  // // run inner PID loop 
  // final_controller_output = pid.pitch_rate_command(k_est.return_gyro_yaw());

  // map controller output to servo value
  // servo_input = map(final_controller_output, -400, 400, 75, 105);
  // servo1.write(servo_input);

  // Serial.println(servo_input);

  if (startRobot == 1) {
    analogWrite(motorPin, 130);
  }

  servo_input = map(deltaDistance, -40, 40, SERVO_MIN, SERVO_MAX);
  if(servo_input < SERVO_MIN) {
    servo_input = SERVO_MIN;
  }
  if(servo_input > SERVO_MAX) {
    servo_input = SERVO_MAX;
  }
  servo1.write(servo_input);
}
