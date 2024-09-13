#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"
#include "gyak_min.h"
#include "linetrace.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出し */
    sta_cyc(SENS_CYC);
    sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}

void boss_task(intptr_t exinf){
    float time[11] = {0.0};
    float velo[11] = {0.0};

    printf("time, velo:\n");
    for(int i=0;i<11;i++){
        printf("%f, ", time[i]);
        printf("%f : ",velo[i]);
    }
    printf("\n");
}


void sens_task(intptr_t exinf){
    /* モータ読み取り */
    // motor_update(arm_motor);
    // motor_update(left_motor);
    // motor_update(right_motor);

    /* ジャイロ読み取り */
    // gyro_sensor_update(gyro_sensor);

    /* カラーセンサ読み取り */
    // color_sensor_update(color_sensor);

}