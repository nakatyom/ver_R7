#include <stdio.h>

#include "app.h"
#include "ev3api.h"
#include "port.h"
#include "linetrace.h"
#include "get_line.h"

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
    sta_cyc(LT_CYC);

    /* タスク終了 */
    ext_tsk();
}

void linetrace_task(intptr_t exinf){
    get_line();
    //linetrace();
}