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
    /* ポ�??��ト設?��? */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出?��? */
    sta_cyc(SENS_CYC);
    sta_cyc(BOSS_CYC);

    /* タスク終�? */
    ext_tsk();
}

#include <math.h>
struct coordinate crnt   = {  0.0,   0.0, 0.0};
struct coordinate target = {100.0, 100.0, 0.0}; // 地点座標なので角度な?��?

void boss_task(intptr_t exinf){
    static int is_head;

    if(0 == is_head){
        float test = calc_TgtVelocity(200.0);

        is_head = 1;
    }
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