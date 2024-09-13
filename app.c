#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"
#include "smartCarry.h"
#include "linetrace.h"
#include "velocity_control.h"
#include "gyak_min.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    

    
    /* タスク呼び出し */
    sta_cyc(SENS_CYC);
    //sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}


void boss_task(intptr_t exinf){
    // printf("僕は邪魔者。");
  
}
int32_t left=0;
int32_t right=0;
int robo_mode=0;

#define ARRAY 50

void sens_task(intptr_t exinf){
    static int cunt;
    static int is_head = 0;
    static float time[ARRAY] = {0.0};
    static float velo[ARRAY] = {0.0};

    if(0 == is_head){
        calc_TgtVelocity(500.0, 30.0, 11, time, velo);

        printf("time:\n");
        for(int i=0;i<ARRAY;i++){
            printf("%f, ", time[i]);
        }
        printf("\ntime:\n");
        for(int i=0;i<ARRAY;i++){
            printf("%f : ",velo[i]);
        }
        printf("\n");
        is_head = 1;
    }
    
    if((float)cunt*0.02 < 10.0){
        float tgtV = get_TgtVelcity((float)cunt*0.02, ARRAY, time, velo);
        printf("crnt_time: %f ", (float)cunt*0.02);
        printf("TgtV: %f\n", tgtV); 
        mid_velocity_control(tgtV+30.0f, 0.0f);
    }
    else{
        motor_stop(left_motor);
        motor_stop(right_motor);
    }

    cunt += 1;

}