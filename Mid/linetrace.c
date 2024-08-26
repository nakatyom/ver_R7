#include "linetrace.h"
#include "velocity_control.h"


float mid_PID_line_pos(float tag, float maj){ 

    const float kp = 0.5f;
    const float ki = 0.0f;
    const float kd = 0.0;

    static float intg;
    static float err_pre;
    static float err;
     
    err_pre = err;
    err = tag - maj;
    intg += err;

    if (intg > 1000.0f)    intg = 1000.0f;
    if (intg < -1000.0f)   intg = -1000.0f;

    return ((err * kp) + (intg * ki) + ((err - err_pre) * kd));
}


void linetrace(void){

    int reflection = ev3_color_sensor_get_reflect(EV3_PORT_1);

    float velo_rot_target = mid_PID_line_pos(25.0f, (float)reflection);

    mid_velocity_control(50.0f, velo_rot_target);
//    mid_velocity_control(50.0f, 0.0f);  // debug
}
