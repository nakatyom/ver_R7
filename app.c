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
    static struct coordinate test_c = {0.0f, 0.0f, 0.0f};
    //static int cunt;
    //static int is_head = 0;
    //static float time[ARRAY] = {0.0};
    //static float velo[ARRAY] = {0.0};

    //float tgt_distance = 1000.0;
    //float tgt_theta = 90.0;
    //float tgt_time = 20.0;
    //float crnt_time = (float)cunt*0.02;

    get_crntCoordinate(&test_c);
    printf("x: %f,y: %f,theta: %f\n",test_c.x, test_c.y, test_c.theta);

    if(1 ==  ev3_touch_sensor_is_pressed(touch_sensor)){
        test_c.x = 0.0;
        test_c.y = 0.0;
    }

/*  
    mid_velocity_control(0.0f, -40.0f);
    if(test_c.theta > 0.95 * tgt_theta){
        motor_stop(left_motor);
        motor_stop(right_motor);      
    }
    
    if(0 == is_head){
        calc_TgtVelocity(tgt_distance, tgt_time, ARRAY, time, velo);

        printf("time:\n");
        for(int i=0;i<ARRAY;i++){
            printf("%f, ", time[i]);
        }
        printf("\nvelocity:\n");
        for(int i=0;i<ARRAY;i++){
            printf("%f : ",velo[i]);
        }
        printf("\n");
        is_head = 1;
    }
    
    if(crnt_time < tgt_time){
        float tgtV = get_TgtVelcity(crnt_time, ARRAY, time, velo);
        printf("crnt_time: %f ", crnt_time);
        printf("TgtV: %f\n", tgtV); 
        mid_velocity_control(tgtV, 0.0f);
    }
    else{
        motor_stop(left_motor);
        motor_stop(right_motor);
    }

    cunt += 1;
*/
}