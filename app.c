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
int LSUM = 0;
int RSUM = 0;

void ichi_task(intptr_t exinf){
    int cyc = 10;
    int LP = 100;
    int RP = 100;
    int32_t LC;
    int32_t RC;
    int LV;
    int RV;

    ev3_motor_set_power(left_motor, LP);
    LC = ev3_motor_get_counts(left_motor);
    LV = (LC*1000)/cyc;
    ev3_motor_reset_counts(left_motor);

    ev3_motor_set_power(right_motor, RP);
    RC = ev3_motor_get_counts(right_motor);
    RV = (RC*1000)/cyc;
    ev3_motor_reset_counts(right_motor);

    if(count == 100){
        LSUM /= 100;
        RSUM /= 100;

        printf("%d, %d\n", RSUM, LSUM);
        
        LSUM = 0;
        RSUM = 0;
        count = 0;
    }
    else{
        LVSUM += LV;
        count += 1;
    }

}
