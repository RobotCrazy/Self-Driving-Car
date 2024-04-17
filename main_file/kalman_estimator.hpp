#ifndef KAL_ESTIMATOR_H
#define KAL_ESTIMATOR_H

#include <Wire.h>

class KAL_ESTIMATOR {
  public:
    void beginDevice(void);
    void calculate_posteriori_angle(void);
    void camera_gyro_kalman_filter(void);
    float return_posteriori_angle(void);

    void get_camera_angle(float heading_measurement);
    float return_camera_angle(void);

    void calculate_gyro_rate(void);
    float return_gyro_yaw(void);
    
    void gyroCal(void);
  private:
    //====== Gyro Callibration Variables =========================
    float yaw_cal;
    int rate_cal;
    //====== Gyro Variables ======================================
    int16_t x_gyro, y_gyro, z_gyro;
    float yaw_rate;
    //====== Accel Variables =====================================
    float camera_angle;
    //====== Kalman Filter Variables =============================
    float kalman_angle = 0;
    float posteriori_uncertainty = 2*2;
    float apriori_uncertainty = 0;

    float apriori_state = 0;
    float posteriori_state = 0;
    float kalman_gain = 0;




    float kalman_output[2] = {0, 0}; // yaw angle prediction followed by its uncertainties
};

#endif