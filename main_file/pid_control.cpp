#include "pid_control.hpp"
#include <Wire.h>

float limit = 400;

void PID_CONTROLLER::output_target_pitch_rate(float kalman_angle, float deltax, float k_weight, float d_weight) {
  
  error_angle_and_d = k_weight*kalman_angle + d_weight*deltax; 
  proportional_angle = kp_angle*error_angle_and_d;
  integral_angle += ki_angle*(error_angle_and_d + previous_error_angle_and_d)*dt/2;

  if (integral_angle > 400) { integral_angle = 400; }
  else if (integral_angle < -400) { integral_angle = -400; }

  derivative_angle = kd_angle*(error_angle_and_d - previous_error_angle_and_d)/dt;
  previous_error_angle_and_d = error_angle_and_d;
  setpoint_rate = proportional_angle + integral_angle + derivative_angle;

  if (setpoint_rate > limit) { setpoint_rate = limit; }
  else if (setpoint_rate < -limit) { setpoint_rate = -limit; }
};
    
float PID_CONTROLLER::pitch_rate_command(float gyro_rate) {

  error_rate = setpoint_rate - gyro_rate;
  proportional_rate = kp_rate*error_rate;
  integral_rate += ki_rate*(error_rate + previous_error_rate)*dt/2;

  if (integral_rate > 400) { integral_rate = 400; }
  else if (integral_rate < -400) { integral_rate = -400; }

  derivative_rate = kd_rate*(error_rate - previous_error_rate)/dt;
  previous_error_rate = error_rate;
  controller_output = proportional_rate + integral_rate + derivative_rate;

  if (controller_output > limit) { controller_output = limit; }
  else if (controller_output < -limit) { controller_output = -limit; }

  return controller_output;
};

void PID_CONTROLLER::reset_pid(void) {
      //====== Errors ==============================================
    error_angle_and_d = 0; 
    error_rate = 0;

    //====== Previous Errors =====================================
    previous_error_angle_and_d = 0; 
    previous_error_rate = 0;

    //====== Integral Terms ===========================================
    integral_angle = 0; 
    integral_rate = 0;

}