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

int count = 0;

void ichi_task(intptr_t exinf){
    int cys = 20;
    int LP = 50;
    int32_t LC;
    int LV;

    ev3_motor_set_power(left_motor, LP);
    LC = ev3_motor_get_counts(left_motor);
    LV = (LC*1000)/20;
    ev3_motor_reset_counts(left_motor);

    if(count == 10){
        printf("%d, %d, %d\n", LP, LC, LV);
        count = 0;
    }
    else{
        count += 1;
    }

}
