#include "app.h"
#include "file_io.c"
#include <stdio.h>

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
    
    printf("Start MainTask!!\n");
    
    /* ライントレースタスクの起動 */
    write_log();
    sta_cyc(NAKA_TASK_CYC);

    /* タスク終了 */
    ext_tsk();
}

void naka_task(intptr_t unused){
    printf("Start Naka Task!!\n");
    
}
