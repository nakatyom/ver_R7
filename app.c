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

void log_task(intptr_t unused){
    u_int8_t amb = 0;
    u_int8_t ref = 0;
    rgb_raw_t color = {0,0,0};
    int16_t dist = 0;

    /* Color Log */
    amb = ev3_color_sensor_get_ambient(color_sensor);
    ref = ev3_color_sensor_get_reflect(color_sensor);
    ev3_color_sensor_get_rgb_raw(color_sensor, &color);
    printColorLog(amb, ref, &color); 

    /* Sonic Log */
    dist = ev3_ultrasonic_sensor_get_distance(sonar_sensor);
    printSonicLog(dist); 
}
