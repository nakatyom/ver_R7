#include <stdio.h>

#include "app.h"
#include "ev3api.h"
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
    sta_cyc(SENS_CYC);
    sta_cyc(MOTOR_CYC);

    /* タスク終了 */
    ext_tsk();
}

int32_t left_counts = 0;
int32_t right_counts = 0;
int left_power = 50;
int right_power = 50;

void sens_task(intptr_t exinf){

}

void motor_task(intptr_t exinf){
    left_counts = ev3_motor_get_counts(left_motor);
    right_counts = ev3_motor_get_counts(right_motor);

    if((left_counts > 180 && left_power > 0) || (left_counts < 0 && left_power < 0)){
        left_power *= -1;
    }

    if((right_counts > 180 && right_power > 0) || (right_counts < 0 && right_power < 0)){
        right_power *= -1;
    }

    ev3_motor_set_power(left_motor, left_power);
    ev3_motor_set_power(right_motor, right_power);
    printf("%d, %d\n",);
}