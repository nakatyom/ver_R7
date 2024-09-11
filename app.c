#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"

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
    static struct coordinate crnt;
    const float tgt_dist = 200.0;

        // get_crntCoordinate(&crnt);
        // printf("x=%f, y=%f, theta=%f\n",crnt.x, crnt.y,crnt.theta);

        if(crnt.x <= 200){
            // float crnt_v = calc_TgtVelocity(tgt_dist);
            mid_velocity_control(0.0f, 0.0f);
            // motor_set_power(left_motor, 50);
            // motor_set_power(right_motor, -50);
        }
        else{
            motor_stop(left_motor);
            motor_stop(right_motor);
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