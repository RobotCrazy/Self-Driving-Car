#ifndef CONTROLLER_H
#define CONTROLLER_H

class PID_CONTROLLER {
  public:
    
    // outer PID loop (this is why it is void, it changes internal object parameters)
    void output_target_pitch_rate(float kalman_angle, float deltax, float k_weight, float d_weight); 

    // inner PID loop
    float pitch_rate_command(float measured);

    // reset integration and error parameters
    void reset_pid(void);
    
  private:
    //====== PID Constants =======================================

    // outer loop is first column, inner loop is second column
    const float kp_angle = 50; const float kp_rate = 60;
    const float ki_angle = 0; const float ki_rate = 6;
    const float kd_angle = 0.2; const float kd_rate = 0.03;

    //====== Errors ==============================================
    float error_angle_and_d = 0; float error_rate = 0;

    //====== Previous Errors (used for the integration term) =====
    float previous_error_angle_and_d = 0; float previous_error_rate = 0;

    //====== PID Terms ===========================================
    float proportional_angle = 0; float proportional_rate = 0;
    float integral_angle = 0; float integral_rate = 0;
    float derivative_angle = 0; float derivative_rate = 0;

    //====== Angular rate setpoint ===========================
    float setpoint_rate = 0;

    //====== Update Rate =========================================
    float dt = 0.004;

    //====== Misc ================================================
    float controller_output = 0;
    
};

#endif