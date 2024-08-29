#include "app.h"
#include "ev3api.h"
#include <stdio.h>

#include "port.h"
#include "Log.h"

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
    
    printf("Start LogTask!!\n");
    sta_cyc(LOG_CYC);


    /* タスク終了 */
    ext_tsk();
}

int motor_p = 50;
int32_t encL = 0;
int32_t encR = 0;

void log_task(intptr_t unused){
    ev3_motor_set_power(left_motor,motor_power);
    ev3_motor_set_power(right_motor,motor_power);

    encL = ev3_motor_get_counts(left_motor);
    encR = ev3_motor_get_counts(right_motor);

    log_EncLR(motor_power,motor_power,encL,encR);
}
