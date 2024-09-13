#include <stdio.h>

#include "ev3api.h"
// #include "common.h"
#include "port.h"
// #include "motor.h"
// # include "gyro.h"
#include "app.h"
// #include "odometry.h"
// #include "gyak_min.h"
// #include "linetrace.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポ�?�ト設�? */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出�? */
    sta_cyc(BOSS_CYC);

    /* タスク終�? */
    ext_tsk();
}



void boss_task(intptr_t exinf){
    mid_velocity_control(0.0f, 50.0f); 

    //static int cunt;
    //static int is_head = 0;
    //static float time[11] = {0.0};
    //static float velo[11] = {0.0};

    //if(0 == is_head){
    //    calc_TgtVelocity(100.0, 10.0, 11, time, velo);

    //    printf("time:\n");
    //    for(int i=0;i<11;i++){
    //        printf("%f, ", time[i]);
    //    }
    //    printf("\ntime:\n");
    //    for(int i=0;i<11;i++){
    //        printf("%f : ",velo[i]);
    //    }
    //    printf("\n");
    //    is_head = 1;
    //}
    //
    //if((float)cunt*0.02 < 10.0){
    //    float tgtV = get_TgtVelcity((float)cunt*0.02, 11, time, velo);
    //    printf("crnt_time: %f ", (float)cunt*0.02);
    //    printf("TgtV: %f\n", tgtV);   
    //}
    //else{
    //    motor_stop(left_motor);
    //    motor_stop(right_motor);
    //}

    //cunt += 1;
}