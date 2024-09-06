#include "linetrace.h"
#include "velocity_control.h"


float mid_PID_line_pos(float tag, float maj,float val){ 
    /* power 90 の時。 */
    /*
    const float kp = 0.2f;
    const float ki = 0.02f;
    const float kd = 0.10f;
    */
    /* power 50 の時。0.72 */
    const float kp = (float)val;
    const float ki = 0.08f;
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


void linetrace(float val_val){

    int reflection = ev3_color_sensor_get_reflect(color_sensor);
    //printf("Reflect:%d\n",reflection);

    float velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,val_val);

    mid_velocity_control(50.0f, -velo_rot_target);
    //printf("%d,%d\n",cnt,reflection);
    //mid_velocity_control(90.0f, 0.0f);  // debug
}
