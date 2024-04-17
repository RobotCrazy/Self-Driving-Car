#include <Wire.h>
#include "kalman_estimator.hpp"
#include <Arduino.h>

void KAL_ESTIMATOR::beginDevice(void) {
  // set clock speed
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);

  // configure MPU6050 to start in power mode
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // access the register 1A (found in datasheet) and write the value 04 
  // which will set a digital lowpass filter of 20Hz on the MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
}

void KAL_ESTIMATOR::gyroCal(void) {
  for(rate_cal = 0; rate_cal < 2000; rate_cal ++) {
    calculate_gyro_rate();
    yaw_cal += yaw_rate;
    delay(1);
  }
  yaw_cal /= 2000;
}

void KAL_ESTIMATOR::get_camera_angle(float heading_measurement) {
  camera_angle = heading_measurement;

}

void KAL_ESTIMATOR::calculate_gyro_rate(void) {

  // set the MPU6050's gyroscope scale factor by accessing the register 1B
  // and sending a hexidecimal value of 80 to set a maximum of 500 degrees / second
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();

  // access the gyroscope values again by accessing register 43
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();

  // this sends a command letting the MPU6050 know that we want to receive 6 bytes
  // starting at register 43
  Wire.requestFrom(0x68, 6);

  // here in a single line we read a byte of data from the MPU6050 into 2 bytes of
  // space, shift the byte over to the other half, and finally read in the second
  // byte where we then do an 'or' operation to merge the two values into one
  // 2-byte value. This process happens for all six gyroscope measurement registers
  x_gyro = Wire.read() << 8 | Wire.read();
  y_gyro = Wire.read() << 8 | Wire.read();
  z_gyro = Wire.read() << 8 | Wire.read();

  // here we have to convert to degrees / second which is done by dividing by
  // the LSB resolution found in the MPU6050 datasheet
  // for reference, LSB/degree/second means "least significant bit per degree per second"
  yaw_rate = (float)z_gyro/65.5 - yaw_cal;
}

void KAL_ESTIMATOR::calculate_posteriori_angle(void) {
  camera_gyro_kalman_filter();
  kalman_angle = kalman_output[1];
  posteriori_uncertainty = kalman_output[2];
}

void KAL_ESTIMATOR::camera_gyro_kalman_filter(void) {
  apriori_state = posteriori_state + 0.004*yaw_rate;
  apriori_uncertainty = posteriori_uncertainty + 0.004*0.004*4*4;
  kalman_gain = apriori_uncertainty*1 / (1*apriori_uncertainty + 3*3);
  posteriori_state = apriori_state + kalman_gain*(camera_angle - apriori_state);
  posteriori_uncertainty = (1-kalman_gain)*apriori_uncertainty;
  kalman_output[1] = posteriori_state;
  kalman_output[2] = posteriori_uncertainty;

}

// Options to access private variables ============================
float KAL_ESTIMATOR::return_camera_angle(void) {
  return camera_angle;
}

float KAL_ESTIMATOR::return_gyro_yaw(void) {
  return yaw_rate;
}

float KAL_ESTIMATOR::return_posteriori_angle(void) {
  return kalman_angle;
}

