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
    int LP = 50;
    int RP = 50;

    ev3_motor_set_power(left_motor, LP);
    ev3_motor_set_power(right_motor, RP);
    
    ev3_motor_reset_count(left_motor);
    ev3_motor_reset_count(right_motor);
    int32_t LC = ev3_motor_get_count(left_motor);
    int32_t RC = ev3_motor_get_count(right_motor);
    int lp = ev3_get_motor_power(left_motor);
    int rp = ev3_get_motor_power(right_motor);

    printf("%d : %d, %d : %d\n", lp, rp, LC, RC);


}
