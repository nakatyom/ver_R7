#include "app.h"
#include "ev3api.h"
#include <stdio.h>

#include "port.h"

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    /* センサー入力ポートの設定 */
    ev3_sensor_config(touch_sensor ,TOUCH_SENSOR);
    ev3_sensor_config(color_sensor ,COLOR_SENSOR);
    ev3_sensor_config(sonar_sensor ,ULTRASONIC_SENSOR);
    ev3_sensor_config(gyro_sensor  ,GYRO_SENSOR);
    
    /* モーター出力ポートの設定 */
    ev3_motor_config(arm_motor     ,LARGE_MOTOR);
    ev3_motor_config(left_motor    ,MEDIUM_MOTOR);
    ev3_motor_config(right_motor   ,MEDIUM_MOTOR);

    /* タスク呼び出し */
    sta_cyc(ICHI_CYC);
    /* タスク終了 */
    ext_tsk();
}



void ichi_task(intptr_t exinf){
int l_power = 50;
int r_power = 50;

float lp = 0.96*50;
l_power = (int)lp

ev3_motor_set_power(left_motor,l_power);
ev3_motor_set_power(right_motor,r_power);
}
