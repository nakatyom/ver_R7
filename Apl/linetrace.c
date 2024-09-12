#include <stdio.h>

#include "ev3api.h"
#include "port.h"
#include "velocity_control.h"
#include "linetrace.h"
#include "odometry.h"

struct coordinate crnt_line = {0.0, 0.0, 0.0} ;

float mid_PID_line_pos(float tag, float maj){ 

    const float kp = 0.3f;
    const float ki = 0.04f;
    const float kd = 0.13f;

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
    get_crntCoordinate(&crnt_line);

    printf("x=%f | y=%f | θ=%f\n",crnt_line.x,crnt_line.y,crnt_line.theta);

    int reflection = ev3_color_sensor_get_reflect(color_sensor);

    float velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection);

    mid_velocity_control(50.0f, -velo_rot_target);
//    mid_velocity_control(50.0f, 0.0f);  // debug
}
